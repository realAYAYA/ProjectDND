// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_AbilityFire.generated.h"

/**
 * 该AnimState的工作，实际上UAnimNotify就可以完成，但后者存在丢帧的bug
 * 这个Bug对于动作游戏的严格动作判定甚至时致命的
 * 为了防止丢帧，使用AnimNotifyState来提供一个窗口期触发
 */
UCLASS()
class UAnimNotifyState_AbilityFire : public UAnimNotifyState
{
	GENERATED_BODY()
	
	//virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	//virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
	//virtual void BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload) override;
	//virtual void BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime) override;
	//virtual void BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload) override;

private:

	bool bDone = false;
	
};
