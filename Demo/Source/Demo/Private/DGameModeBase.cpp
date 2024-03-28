// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameModeBase.h"

#include "DCharacterManager.h"
#include "DGameInstance.h"
#include "TurnBasedBattleInstance.h"
#include "DPlayerController.h"
#include "GameFramework/PlayerState.h"

void ADGameModeBase::BuildBattleWithAllCharacters()
{
	const auto* GameInstance = Cast<UDGameInstance>(GetGameInstance());
	if (!GameInstance)
		return;

	ATurnBasedBattleInstance* BattleInstance = GetWorld()->SpawnActor<ATurnBasedBattleInstance>();

	GameInstance->CharacterManager->Foreach([BattleInstance](ADCharacter* Character) -> bool
	{
		// 角色死亡或其它某种状态不得参加战斗
		if (auto* PC = Cast<ADPlayerController>(Character->GetPlayerState()->GetPlayerController()))
		{
			PC->GetInBattle(BattleInstance);
			BattleInstance->CharacterIdList.Add(Character->GetRoleId());
			BattleInstance->CharacterList.Add(Character);
		}
		
		return true;
	});
	
}
