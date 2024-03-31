#include "DGameplayEffect.h"

#include "AbilitySystemLog.h"
#include "GameplayAbilitySystem/DAbilitySystemComponent.h"
#include "GameplayAbilitySystem/GameplayAbilitySystemGlobalTags.h"

#include "Engine/PackageMapClient.h"

FGameplayAbilityGlobalTags FGameplayAbilityGlobalTags::GasTags;

/*
FTurnBasedActiveGameplayEffect& FTurnBasedActiveGameplayEffect::operator=(FTurnBasedActiveGameplayEffect&& Other) noexcept
{
	return *this;
}

FTurnBasedActiveGameplayEffect& FTurnBasedActiveGameplayEffect::operator=(const FTurnBasedActiveGameplayEffect& Other)
{
	return *this;
}*/

void FTurnBasedActiveGameplayEffect::PreReplicatedRemove(const FTurnBasedActiveGameplayEffectsContainer& InArray)
{
	
}

void FTurnBasedActiveGameplayEffect::PostReplicatedAdd(const FTurnBasedActiveGameplayEffectsContainer& InArray)
{
	
}

void FTurnBasedActiveGameplayEffect::PostReplicatedChange(const FTurnBasedActiveGameplayEffectsContainer& InArray)
{
	/*if (Spec.Def == nullptr)
	{
		ABILITY_LOG(Error, TEXT("FActiveGameplayEffect::PostReplicatedChange Received ReplicatedGameplayEffect with no UGameplayEffect def. (%s)"), *Spec.GetEffectContext().ToString());
		return;
	}

	if (Spec.Modifiers.Num() != Spec.Def->Modifiers.Num())
	{
		// This can happen with older replays, where the replicated Spec.Modifiers size changed in the newer Spec.Def
		Spec.Modifiers.Empty();
		return;
	}*/

	// Handle potential duration refresh
	if (DurationTurn != ClientCachedTurn)
	{
		//RecomputeStartWorldTime(InArray);
		//CachedStartServerWorldTime = StartServerWorldTime;

		//const_cast<FActiveGameplayEffectsContainer&>(InArray).OnDurationChange(*this);
	}
}

FTurnBasedActiveGameplayEffect* FTurnBasedActiveGameplayEffectsContainer::GetActiveGameplayEffect(
	const FActiveGameplayEffectHandle& Handle)
{
	for (FTurnBasedActiveGameplayEffect& Effect : GameplayEffects_Internal)
	{
		if (Effect.ActiveGameplayEffectHandle == Handle)
		{
			return &Effect;
		}
	}
	
	return nullptr;
}

const FTurnBasedActiveGameplayEffect* FTurnBasedActiveGameplayEffectsContainer::GetActiveGameplayEffect(
	const FActiveGameplayEffectHandle& Handle) const
{
	for (const FTurnBasedActiveGameplayEffect& Effect : GameplayEffects_Internal)
	{
		if (Effect.ActiveGameplayEffectHandle == Handle)
		{
			return &Effect;
		}
	}
	
	return nullptr;
}

FTurnBasedActiveGameplayEffect* FTurnBasedActiveGameplayEffectsContainer::ApplyActiveGameplayEffect(
	const FActiveGameplayEffectHandle& Handle,
	const UDGameplayEffect* GameplayEffect,
	int32 CustomDuration)
{
	if (CustomDuration <= 0)
		CustomDuration = GameplayEffect->TurnDuration;
	
	FTurnBasedActiveGameplayEffect* TurnBasedActiveGameplayEffect = GetActiveGameplayEffect(Handle);
	if (!TurnBasedActiveGameplayEffect)
	{
		const int32 Idx = GameplayEffects_Internal.Add(FTurnBasedActiveGameplayEffect(Handle, CustomDuration));
		return &GameplayEffects_Internal[Idx];
	}
	else
	{
		if (GameplayEffect->StackDurationRefreshPolicy == EGameplayEffectStackingDurationPolicy::RefreshOnSuccessfulApplication)
		{
			TurnBasedActiveGameplayEffect->DurationTurn = CustomDuration;
		}

		if (GameplayEffect->StackPeriodResetPolicy == EGameplayEffectStackingPeriodPolicy::ResetOnSuccessfulApplication)
		{
			TurnBasedActiveGameplayEffect->CurrentTurn = 0;
		}

		MarkItemDirty(*TurnBasedActiveGameplayEffect);
	}

	return TurnBasedActiveGameplayEffect;
}


bool FTurnBasedActiveGameplayEffectsContainer::RemoveActiveGameplayEffect(const FActiveGameplayEffectHandle& Handle)
{
	int32 Idx = INDEX_NONE;
	for (int32 i = 0; i < GameplayEffects_Internal.Num(); i++)
	{
		const FTurnBasedActiveGameplayEffect& Effect = GameplayEffects_Internal[i];
		if (Effect.ActiveGameplayEffectHandle == Handle)
		{
			Idx = i;
			break;
		}
	}

	if (Idx == INDEX_NONE)
		return false;
	
	GameplayEffects_Internal.RemoveAtSwap(Idx);
	MarkArrayDirty();
	return true;
}

void FTurnBasedActiveGameplayEffectsContainer::CheckTurnDuration()
{
	TArray<int32> RemoveList;
	for (int32 i = 0; i < GameplayEffects_Internal.Num(); i++)
	{
		FTurnBasedActiveGameplayEffect& TurnBasedActiveGameplayEffect = GameplayEffects_Internal[i];
		const FActiveGameplayEffect* ActiveGameplayEffect = Owner->GetActiveGameplayEffect(TurnBasedActiveGameplayEffect.ActiveGameplayEffectHandle);

		const UDGameplayEffect* GameplayEffectDef = Cast<UDGameplayEffect>(ActiveGameplayEffect->Spec.Def);
		if (!GameplayEffectDef)
			continue;
		
		TurnBasedActiveGameplayEffect.CurrentTurn += 1;
		if (GameplayEffectDef->TurnPeriod > 0 && TurnBasedActiveGameplayEffect.CurrentTurn % GameplayEffectDef->TurnPeriod != 0)
		{
			// 施加周期效果
			Owner->ExecuteTurnBasedPeriodicEffect(TurnBasedActiveGameplayEffect.ActiveGameplayEffectHandle);
		}
		
		if (TurnBasedActiveGameplayEffect.CurrentTurn == TurnBasedActiveGameplayEffect.DurationTurn)
		{
			Owner->RemoveActiveGameplayEffect(TurnBasedActiveGameplayEffect.ActiveGameplayEffectHandle, - 1);
			RemoveList.Add(i);
		}
	}

	for (int32 i = 0; i < RemoveList.Num() - 1; i++)
	{
		GameplayEffects_Internal.RemoveAtSwap(RemoveList[i], 1, false);
	}
	GameplayEffects_Internal.RemoveAtSwap(RemoveList[RemoveList.Num() - 1], 1, true);// 最后删除一次对数组进行内存清理

	if (RemoveList.Num() > 0)
		MarkArrayDirty();
}

int32 FTurnBasedActiveGameplayEffectsContainer::GetActiveEffectRemainingTurn(
	const FActiveGameplayEffectHandle& ActiveHandle) const
{
	for (const auto& Elem : GameplayEffects_Internal)
	{
		if (Elem.ActiveGameplayEffectHandle == ActiveHandle)
		{
			return Elem.DurationTurn - Elem.CurrentTurn;
		}
	}
	
	return 0;
}

void FTurnBasedActiveGameplayEffectsContainer::RegisterWithOwner(UDAbilitySystemComponent* InOwner)
{
	if (Owner != InOwner && InOwner != nullptr)
	{
		Owner = InOwner;
		OwnerIsNetAuthority = Owner->IsOwnerActorAuthoritative();
	}
}

bool FTurnBasedActiveGameplayEffectsContainer::NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
{
	// NOTE: Changes to this testing needs to be reflected in GetReplicatedCondition(), which is what is used if the container has a dynamic lifetime condition, COND_Dynamic, set.
	// These tests are only needed when sending and the instance isn't using the COND_Dynamic lifetime condition, in which case NetDeltaSerialize wouldn't be called unless it should replicate.
	if (!IsUsingReplicationCondition() && DeltaParams.Writer != nullptr && Owner != nullptr)
	{
		const EGameplayEffectReplicationMode ReplicationMode = Owner->ReplicationMode;
		if (ReplicationMode == EGameplayEffectReplicationMode::Minimal)
		{
			return false;
		}
		else if (ReplicationMode == EGameplayEffectReplicationMode::Mixed)
		{
			if (UPackageMapClient* Client = Cast<UPackageMapClient>(DeltaParams.Map))
			{
				UNetConnection* Connection = Client->GetConnection();

				// Even in mixed mode, we should always replicate out to client side recorded replays so it has all information.
				if (!Connection->IsReplay() || IsNetAuthority())
				{
					// In mixed mode, we only want to replicate to the owner of this channel, minimal replication
					// data will go to everyone else.
					const AActor* ParentOwner = Owner->GetOwner();
					const UNetConnection* ParentOwnerNetConnection = ParentOwner->GetNetConnection();
					if (!ParentOwner->IsOwnedBy(Connection->OwningActor) && (ParentOwnerNetConnection != Connection))
					{
						bool bIsChildConnection = false;
						for (const UChildConnection* ChildConnection : Connection->Children)
						{
							if (ParentOwner->IsOwnedBy(ChildConnection->OwningActor) || (ChildConnection == ParentOwnerNetConnection))
							{
								bIsChildConnection = true;
								break;
							}
						}
						
						if (!bIsChildConnection)
						{
							return false;
						}
					}
				}
			}
		}
	}
	
	const bool RetVal = FastArrayDeltaSerialize<FTurnBasedActiveGameplayEffect>(GameplayEffects_Internal, DeltaParams, *this);

	// This section has been moved into new PostReplicatedReceive() method that is invoked after every call to FastArrayDeltaSerialize<> that results in data being modified
	
	return RetVal;
}

void FTurnBasedActiveGameplayEffectsContainer::OnTurnCountChange(
	FActiveGameplayEffect& ActiveEffect,
	const int32 OldStackCount,
	const int32 NewStackCount)
{
	Owner;
}

UDGameplayEffect::UDGameplayEffect()
{
	
}
