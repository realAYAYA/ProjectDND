// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "DEditorStyle.h"

class FDEditorCommands : public TCommands<FDEditorCommands>
{
public:

	FDEditorCommands()
		: TCommands<FDEditorCommands>(TEXT("DEditor"), NSLOCTEXT("Contexts", "DEditor", "DEditor Plugin"), NAME_None, FDEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
