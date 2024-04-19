#include "GA_Melee.h"

UGA_Melee::UGA_Melee()
{
}

void UGA_Melee::ReceiveTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	CacheTargetData = TargetDataHandle;

	// Todo 检测数据合法性，取消技能
	// Todo 计算消耗 施加CD
	// Todo 通知其它角色我要施法了，近战技能可能会被招架
	
	// 收到来自客户端的数据，进行最终施法(攻击)流程
	MontageSetNextSectionName(FName("Loop"), FName("OnFire"));
}

void UGA_Melee::OnNotifyReceivedWithComponent(UDAbilitySystemComponent* Asc)
{
	// Todo 施加近战攻击效果
	// Todo 可能被闪避
}
