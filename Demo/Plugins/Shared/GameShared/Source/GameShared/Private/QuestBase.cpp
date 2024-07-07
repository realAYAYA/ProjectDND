#include "QuestBase.h"

EQuestState UQuestSystemBase::CheckState(const int32 Id)
{
	if (const auto* Quest = GetQuest(Id))
		return CheckState(*Quest);
	
	return EQuestState::InValid;
}

EQuestState UQuestSystemBase::CheckState(const FQuestItem& Quest)
{
	// Todo 检查超时
	if (Quest.BeginDate != 0 && Quest.TimeLimit != 0)
	{
		
	}
	
	for (const auto& Requirement : Quest.Requirements)
	{
		//if (Requirement.Type)
	}

	return EQuestState::InValid;
}

void UQuestSystemBase::Update(const int32 Type, const int32 TargetId, const int32 Num, const bool bOverride)
{
	for (auto& Quest : QuestList)
	{
		UpdateSingleQuest(Quest, Type, TargetId, Num, bOverride);
	}
}

void UQuestSystemBase::UpdateSingleQuest(FQuestItem& Quest, const int32 Type, const int32 TargetId, const int32 Num, const bool bOverride)
{
	for (auto& Req : Quest.Requirements)
	{
		// TargetId为0时，指任意Id的目标都可满足计数条件
		if (Req.Type == Type && (Req.TargetId == 0 || Req.TargetId == TargetId))
		{
			if (bOverride)
				Quest.Counter.Set(Type, TargetId, Num);
			else
				Quest.Counter.Add(Type, TargetId, Num);
		}
	}
}

bool UQuestSystemBase::AcceptQuest(const int32 Id)
{
	return false;
}

bool UQuestSystemBase::GiveUpQuest(const int32 Id)
{
	return false;
}

bool UQuestSystemBase::SubmitQuest(const int32 Id)
{
	return false;
}

FQuestItem* UQuestSystemBase::GetQuest(const int32 Id)
{
	const int32 Index = GetQuestIndex(Id);
	return Index != INDEX_NONE ? &QuestList[Index] : nullptr;
}

int32 UQuestSystemBase::GetQuestIndex(const int32 Id)
{
	int32 i = 0;
	for (const auto& Quest : QuestList)
	{
		if (Quest.Id == Id)
		{
			check(AcceptedQuestIdList.Contains(Id));// 异常：任务并不在接受列表中就能查询
			return i;
		}

		++i;
	}

	return INDEX_NONE;
}

FQuestItem& UQuestSystemBase::InternalAddQuest(const int32 Id)
{
	AcceptedQuestIdList.Add(Id);
	return QuestList[QuestList.AddZeroed()];
}

FQuestItem UQuestSystemBase::InternalRemoveQuest(const int32 Id)
{
	FQuestItem Out;
	const int32 Index = GetQuestIndex(Id);
	if (Index != INDEX_NONE)
	{
		Out = QuestList[Index];
		AcceptedQuestIdList.Remove(Id);
		QuestList.RemoveAtSwap(Index, 1, false);
	}

	return Out;
}

void UQuestSystemBase::InternalRemoveQuest(const FQuestItem* Quest)
{
	if (Quest)
	{
		const int32 Index = GetQuestIndex(Quest->Id);
		if (Index != INDEX_NONE)
		{
			AcceptedQuestIdList.Remove(Quest->Id);
			QuestList.RemoveAtSwap(Index, 1, false);
		}
	}
}
