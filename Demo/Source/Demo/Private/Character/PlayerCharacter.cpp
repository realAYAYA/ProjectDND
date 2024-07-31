// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Inventory/DInventoryComponent.h"

ADPlayerCharacter::ADPlayerCharacter()
{
	InventoryComponent = CreateDefaultSubobject<UDInventoryComponent>(TEXT("InventoryComponent"));
	InventoryComponent->SetIsReplicated(true);
}

// Called to bind functionality to input
void ADPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}