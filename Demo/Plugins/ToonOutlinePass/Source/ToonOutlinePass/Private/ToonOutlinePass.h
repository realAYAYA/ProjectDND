#pragma once
#include "Rendering/CustomRenderPass.h"


class FToonOutlinePass final : public FCustomRenderPassBase
{
	
public:
	
	FToonOutlinePass(
		const FString& InDebugName,
		ERenderMode InRenderMode,
		ERenderOutput InRenderOutput,
		const FIntPoint& InRenderTargetSize)
		: FCustomRenderPassBase(InDebugName, InRenderMode, InRenderOutput, InRenderTargetSize)
	{
		//RenderMode;
		//RenderOutput;
		//RenderTargetSize
	}
	
	//virtual void OnBeginPass(FRDGBuilder& GraphBuilder) override;
	//virtual void OnPreRender(FRDGBuilder& GraphBuilder) override;
	//virtual void OnPostRender(FRDGBuilder& GraphBuilder) override;
	//virtual void OnEndPass(FRDGBuilder& GraphBuilder) override;
};
