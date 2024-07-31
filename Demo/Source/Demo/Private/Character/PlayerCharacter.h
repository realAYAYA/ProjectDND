// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DCharacter.h"
#include "PlayerCharacter.generated.h"

class UDInventoryComponent;
/**
 * 
 */
UCLASS()
class ADPlayerCharacter : public ADCharacter
{
	GENERATED_BODY()

public:

	ADPlayerCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDInventoryComponent* InventoryComponent;
};
