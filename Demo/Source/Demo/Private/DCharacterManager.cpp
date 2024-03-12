// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacterManager.h"

void UDCharacterManager::Init()
{
	Reset();
}

void UDCharacterManager::Reset()
{
	Characters.Reset();
}

ADCharacter* UDCharacterManager::Find(const int64 Id)
{
	return Characters.Contains(Id) ? *Characters.Find(Id) : nullptr;
}

void UDCharacterManager::RegisterCharacter(const int64 Id, ADCharacter* In)
{
	Characters.Add(Id, In);
}

void UDCharacterManager::UnRegisterCharacter(const int64 Id)
{
	Characters.Remove(Id);
}

int64 UDCharacterManager::GenerateRoleId()
{
	return ++SerialNum;
}

void UDCharacterManager::Foreach(const TFunction<bool(ADCharacter*)>& InFunc)
{
	for (const auto Elem : Characters)
	{
		if (Elem.Value)
		{
			if (!InFunc(Elem.Value))
				return;
		}
	}
}
