// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DCharacter.generated.h"

class ATurnBasedBattleInstance;
class UDAbilitySystemComponent;

UCLASS()
class ADCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDAbilitySystemComponent* AbilitySystemComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostNetInit() override;

public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	
	UPROPERTY(BlueprintReadOnly, Category = "ProjectD", ReplicatedUsing = OnBattleInstance)
	ATurnBasedBattleInstance* BattleInstance;
	void SetBattleInstance(ATurnBasedBattleInstance* In);// Called by server

	UFUNCTION(BlueprintImplementableEvent, Category = "ProjectD", DisplayName = "OnBattleInstance")
	void K2_OnBattleInstance();

	UFUNCTION(BlueprintImplementableEvent, Category = "ProjectD", DisplayName = "YourTurn")
	void K2_YourTurn();

	UFUNCTION(BlueprintImplementableEvent, Category = "ProjectD", DisplayName = "BattleEnd")
	void K2_BattleEnd();

	UFUNCTION()
	void OnBattleInstance();
	
	UFUNCTION(Client, Reliable)
	void NotifyYourTurn();
	void YourTurn();// Called by Server

	void ReqTurnEnd();// Called by Server

	UFUNCTION(Client, Reliable)
	void OnBattleEnd();

private:


	/** 网络同步相关*/
	
public:

	UFUNCTION(Blueprintable, Category = "ProjectD")
	int64 GetRoleId() const { return ReplicatedRoleId; }

private:

	UPROPERTY(ReplicatedUsing = OnCharacterIdChange)
	int64 ReplicatedRoleId = 0;
	int64 OldRoleId = 0;

	UFUNCTION()
	void OnCharacterIdChange();
};
