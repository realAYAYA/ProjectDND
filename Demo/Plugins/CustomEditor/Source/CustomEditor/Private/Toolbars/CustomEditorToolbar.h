#pragma once


class FCustomEditorToolbar
{
	
public:

	virtual ~FCustomEditorToolbar() = default;
	FCustomEditorToolbar()
	{
		ContextObject = nullptr;
	}
	
	void BindCommands();
	
	/** This function will be bound to Command. */
	//void StartGameService_Executed();
	//void StopGameService_Executed();
	void ShowGddInFileExplorer_Executed();
	void ShowExcelInFileExplorer_Executed();
	void UpdateGdd_Executed();
	void ReloadGdd_Executed();
	//void UpdatePb_Executed();
	void GenerateWidgetTsFile_Executed();
	

	TSharedPtr<FUICommandList> GetCommandList() const
	{
		return CommandList;
	}

private:
	
	TSharedRef<SWidget> GenerateMenuContent(const TSharedPtr<FUICommandList>& InCommandList) const;
	void BuildToolbar(FToolBarBuilder& ToolbarBuilder, UObject* InContextObject);

	TSharedPtr<FUICommandList> CommandList;

	UObject* ContextObject = nullptr;// 当前操作文件（蓝图）上下文
};