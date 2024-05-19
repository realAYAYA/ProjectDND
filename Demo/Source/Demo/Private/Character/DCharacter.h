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
	
	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	UDCharacterDataAsset* CharacterDataAsset;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UDAbilitySystemComponent* GetDAbilitySystemComponent() const { return AbilitySystemComponent; }
	
protected:

	// 在BeginPlay之前执行
	virtual void BeginReplication() override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 网络同步初始化后执行
	virtual void PostNetInit() override;

	virtual void BeginDestroy() override;

	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDAbilitySystemComponent* AbilitySystemComponent;
	
public:
	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(BlueprintReadOnly, Category = "ProjectD")
	ATurnBasedBattleInstance* BattleInstance;

	UFUNCTION(BlueprintImplementableEvent, Category = "ProjectD", DisplayName = "BattleBegin")
	void K2_BattleBegin();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "ProjectD", DisplayName = "MyTurn")
	void K2_MyTurn();

	UFUNCTION(BlueprintImplementableEvent, Category = "ProjectD", DisplayName = "BattleEnd")
	void K2_BattleEnd();

	void OnBattleBegin();
	void MyTurn();
	void OnBattleEnd();

	bool InBattle() const;

	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	UDAttributeSet* GetAttributeSet() const { return AttributeSet; }

private:

	// 角色移动力变成0时将无法移动
	void OnMoveDistanceChange(const FOnAttributeChangeData& Data) const;

	UPROPERTY(Transient)
	UDAttributeSet* AttributeSet;
	
public:

	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	int64 GetRoleId() const { return RoleId; }

	UPROPERTY(BlueprintReadOnly, Replicated)
	bool bReadyTurnEnd = false;// 该角色当前准备结束回合

private:

	// 角色唯一Id，由服务器分发
	UPROPERTY(ReplicatedUsing = OnRep_CharacterId)
	int64 RoleId = 0;
	int64 OldRoleId = 0;

	UFUNCTION()
	void OnRep_CharacterId();

	// 当前角色的控制者Id, 对应角色的当前控制权归属, 它可以是SteamId或其它
	UPROPERTY(Replicated)
	uint64 ControllerId = 0;

	UFUNCTION()
	void OnRep_ControllerId();

	// Only called by Server
	virtual void InitCharacterData();
};
