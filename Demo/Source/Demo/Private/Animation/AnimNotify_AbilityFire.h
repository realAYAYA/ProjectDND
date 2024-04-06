// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;


	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	TSubclassOf<UGA_WithProjectile> AbilityClassToNotify;
	
};
