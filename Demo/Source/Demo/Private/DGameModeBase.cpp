// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameModeBase.h"
#include "TurnBasedBattleInstance.h"

void ADGameModeBase::BuildBattleWithAllCharacters()
{
	ATurnBasedBattleInstance* BattleInstance = GetWorld()->SpawnActorDeferred<ATurnBasedBattleInstance>(BattleInstanceClass, FTransform(), nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (!BattleInstance)
		return;
	
	BattleInstance->SetReplicates(true);

	BattleInstances.Add(BattleInstance);

	ADCharacter::Foreach([BattleInstance](const ADCharacter* Character) -> bool
	{
		// Todo 角色死亡或其它某种状态不得参加战斗
		BattleInstance->CharacterList.Add(Character->GetRoleId());
		
		return true;
	});

	BattleInstance->BeginBattle();
	BattleInstance->FinishSpawning(FTransform());
}
