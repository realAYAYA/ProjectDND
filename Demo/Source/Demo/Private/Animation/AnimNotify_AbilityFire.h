// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_AbilityFire.generated.h"

class UGA_WithProjectile;
/**
 * 
 */
UCLASS()
class UAnimNotify_AbilityFire : public UAnimNotify
{
	GENERATED_BODY()

public:

	UPROPERTY(EditInstanceOnly, Category = "ProjectD|AnimNotify")
	FGameplayTag AbilityToNotify;
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
