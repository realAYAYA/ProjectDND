// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AbilityFire.h"

#include "Character/DCharacter.h"
#include "GameplayAbilitySystem/DAbilitySystemComponent.h"
#include "GameplayAbilitySystem/Abilities/GA_WithProjectile.h"

void UAnimNotify_AbilityFire::Notify(
	USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	if (const auto* Character = Cast<ADCharacter>(MeshComp->GetOwner()); Character && Character->GetDAbilitySystemComponent())
	{
		Character->GetDAbilitySystemComponent()->NotifyAbilityFireOrHit(AbilityClassToNotify.Get());
	}
	
	Super::Notify(MeshComp, Animation, EventReference);
}
