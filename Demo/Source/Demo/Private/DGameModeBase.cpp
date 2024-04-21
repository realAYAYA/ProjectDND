// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameModeBase.h"
#include "DCharacterManager.h"
#include "DGameInstance.h"
#include "DPlayerController.h"
#include "TurnBasedBattleInstance.h"

#include "GameFramework/PlayerState.h"


void ADGameModeBase::BuildBattleWithAllCharacters()
{
	const auto* GameInstance = Cast<UDGameInstance>(GetGameInstance());
	if (!GameInstance)
		return;

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;
	
	ATurnBasedBattleInstance* BattleInstance = GetWorld()->SpawnActor<ATurnBasedBattleInstance>(BattleInstanceClass, FTransform(), SpawnInfo);
	if (!BattleInstance)
		return;
	
	BattleInstance->SetReplicates(true);

	BattleInstances.Add(BattleInstance);

	GameInstance->CharacterManager->Foreach([BattleInstance](ADCharacter* Character) -> bool
	{
		// 角色死亡或其它某种状态不得参加战斗
		if (auto* PC = Cast<ADPlayerController>(Character->GetPlayerState()->GetPlayerController()))
		{
			BattleInstance->CharacterList.Add(Character);
		}
		
		return true;
	});

	BattleInstance->BeginBattle();
}
