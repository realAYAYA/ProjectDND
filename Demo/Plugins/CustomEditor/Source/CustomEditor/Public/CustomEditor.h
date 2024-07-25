// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCustomEditor, Log, All);

class FToolBarBuilder;
class FMenuBuilder;

class FCustomEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	//void StartGameService_Executed();
	//void StopGameService_Executed();
	void ShowGddInFileExplorer_Executed();
	void ShowExcelInFileExplorer_Executed();
	void UpdateGdd_Executed();
	void ReloadGdd_Executed();
	//void UpdatePb_Executed();
	void GenerateWidgetTsFile_Executed();
	
private:

	void RegisterMenus();

	static void BuildToolbar(UToolMenu* MenuBuilder);

private:
	
	TSharedPtr<class FUICommandList> PluginCommands;

	UObject* ContextObject = nullptr;// 当前操作文件（蓝图）上下文
};
