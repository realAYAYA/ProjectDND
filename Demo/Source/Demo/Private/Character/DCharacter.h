// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GameplayEffectTypes.h"

#include "DCharacter.generated.h"

class UDCharacterDataAsset;
class UDAttributeSet;
class ATurnBasedBattleInstance;
class UDAbilitySystemComponent;


UCLASS()
class ADCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	UDCharacterDataAsset* CharacterDataAsset;
	
protected:

	// 在BeginPlay之前执行
	virtual void BeginReplication() override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 网络同步初始化后执行
	virtual void PostNetInit() override;

	virtual void BeginDestroy() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

public:
	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;


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

	UFUNCTION(Client, Reliable)
	void NotifyBattleEnd();

	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	UDAttributeSet* GetAttributeSet() const { return AttributeSet; }

private:

	// 角色移动力变成0时将无法移动
	void OnMoveDistanceChange(const FOnAttributeChangeData& Data) const;

	UPROPERTY(Transient)
	UDAttributeSet* AttributeSet;

	/** 网络同步相关*/
	
public:

	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	int64 GetRoleId() const { return ReplicatedRoleId; }

private:

	UPROPERTY(ReplicatedUsing = OnCharacterIdChange)
	int64 ReplicatedRoleId = 0;
	int64 OldRoleId = 0;

	UFUNCTION()
	void OnCharacterIdChange();

	// Only called by Server
	virtual void InitCharacterData();
};
