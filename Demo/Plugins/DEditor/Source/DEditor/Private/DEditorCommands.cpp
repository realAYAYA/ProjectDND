// Copyright Epic Games, Inc. All Rights Reserved.

#include "DEditorCommands.h"

#define LOCTEXT_NAMESPACE "FDEditorModule"

void FDEditorCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "DEditor", "Execute DEditor action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
