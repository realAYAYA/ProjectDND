// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FGameCommonModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};


class GAMECOMMON_API FGameUtils
{
	
public:

	/**
	 * 百分之X的概率
	 */
	static bool RollWithPercent(const float Percent)
	{
		const int32 Roll = FMath::RandRange(0, 99);
		return Roll < Percent ? true : false;
	}

	/**
	 * 千分之X的概率
	 */
	static bool RollWithThousand(const float Thousand)
	{
		const int32 Roll = FMath::RandRange(0, 999);
		return Roll < Thousand ? true : false;
	}

	/**
	 * 万分之X的概率
	 */
	static bool RollWithTenThousand(const float TenThousand)
	{
		const int32 Roll = FMath::RandRange(0, 9999);
		return Roll < TenThousand ? true : false;
	}
};