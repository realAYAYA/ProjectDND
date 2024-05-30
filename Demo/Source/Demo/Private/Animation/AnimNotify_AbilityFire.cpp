// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AbilityFire.h"

#include "Character/DCharacter.h"
#include "GameplayAbilitySystem/DAbilitySystemComponent.h"

void UAnimNotify_AbilityFire::Notify(
	USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	if (const auto* Character = Cast<ADCharacter>(MeshComp->GetOwner()); Character && Character->GetDAbilitySystemComponent())
	{
		Character->GetDAbilitySystemComponent()->OnNotifyReceived(GetNotifyName());
	}

/*#if WITH_EDITOR
	UE_LOG(LogProjectD, Log, TEXT("技能组件收到动画通知: %s, 是否为服务器端? %d"), *this->GetNotifyName(), MeshComp->GetOwner()->HasAuthority());
#endif*/
	
	Super::Notify(MeshComp, Animation, EventReference);
}
