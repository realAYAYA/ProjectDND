// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBasedBattleInstance.h"

// Sets default values
ATurnBasedBattleInstance::ATurnBasedBattleInstance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
}

// Called when the game starts or when spawned
void ATurnBasedBattleInstance::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurnBasedBattleInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurnBasedBattleInstance::OnTurnNumChanged()
{
	
}

void ATurnBasedBattleInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

	
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

