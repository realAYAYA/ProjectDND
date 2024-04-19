#include "GA_Melee.h"

UGA_Melee::UGA_Melee()
{
}

void UGA_Melee::ReceiveTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	CacheTargetData = TargetDataHandle;

	// Todo 播放攻击动画
}

void UGA_Melee::OnNotifyReceivedWithComponent(UDAbilitySystemComponent* Asc)
{
	// Todo 施加近战攻击效果
	// Todo 可能被闪避
}
