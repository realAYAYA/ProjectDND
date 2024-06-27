// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AbilityFire.h"

#include "Character/DCharacter.h"
#include "GameplayAbilitySystem/DAbilitySystemComponent.h"

void UAnimNotify_AbilityFire::Notify(
	USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	const auto* Character = Cast<ADCharacter>(MeshComp->GetOwner());
	if (Character && Character->HasAuthority())
	{
		Character->GetDAbilitySystemComponent()->OnNotifyReceived(GetNotifyName(), AbilityToNotify);
	}
	
	Super::Notify(MeshComp, Animation, EventReference);
}
