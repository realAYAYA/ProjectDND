// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameModeBase.h"

#include "DGameInstance.h"
#include "TurnBasedBattleInstance.h"

void ADGameModeBase::BuildBattleWithAllCharacters()
{
	const auto* GameInstance = Cast<UDGameInstance>(GetGameInstance());
	if (!GameInstance)
		return;

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;
	
	ATurnBasedBattleInstance* BattleInstance = GetWorld()->SpawnActor<ATurnBasedBattleInstance>(BattleInstanceClass, FTransform(), SpawnInfo);
	BattleInstance->SetReplicates(true);

	BattleInstances.Add(BattleInstance);
}
