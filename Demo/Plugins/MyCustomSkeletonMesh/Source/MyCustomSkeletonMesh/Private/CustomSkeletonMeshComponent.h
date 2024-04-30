#pragma once

#include "CoreMinimal.h"
#include "CustomSkeletonMeshComponent.generated.h"

struct FMyCustomVertexFactory: public FLocalVertexFactory
{
	DECLARE_VERTEX_FACTORY_TYPE(FMyCustomVertexFactory)

public:

	FMyCustomVertexFactory(ERHIFeatureLevel::Type InFeatureLevel) : FLocalVertexFactory(InFeatureLevel, "MyCustomVertexFactory")
	{
		
	}

	static void ModifyCompilationEnvironment(const FVertexFactoryShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);
	static bool ShouldCompilePermutation(const FVertexFactoryShaderPermutationParameters& Parameters);

	virtual void InitRHI(FRHICommandListBase& RHICmdList) override;
	void Init(const FStaticMeshVertexBuffers* VertexBuffer);
	virtual void ReleaseRHI() override;
	
};


/**
 * 
 */
UCLASS(HideCategories = (UObject, LOD), meta = (BlueprintSpawnableComponent), ClassGroup = Rendering)
class UCustomSkeletonMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()


public:

	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
};

class FMyCustomPrimitiveSceneProxy : public FPrimitiveSceneProxy
{

public:
	
	explicit FMyCustomPrimitiveSceneProxy(UCustomSkeletonMeshComponent* InComponent)
		: FPrimitiveSceneProxy(InComponent)
	, MaterialRelevance(InComponent->GetMaterialRelevance(GetScene().GetFeatureLevel()))
	, VertexFactory(InComponent->GetWorld()->GetFeatureLevel())
	, MyMesh(InComponent->GetStaticMesh())
	, Component(InComponent)
	{
		
	}

	virtual ~FMyCustomPrimitiveSceneProxy() override
	{
		VertexFactory.ReleaseResource();
	}

	virtual SIZE_T GetTypeHash() const override
	{
		static size_t UniquePointer;
		return reinterpret_cast<size_t>(&UniquePointer);
	}

	virtual void CreateRenderThreadResources() override
	{
		if (MyMesh)
			VertexFactory.Init(&MyMesh->GetRenderData()->LODResources[0].VertexBuffers);
	}

	virtual bool CanBeOccluded() const override
	{
		return MaterialRelevance.bDisableDepthTest;
	}

	virtual uint32 GetMemoryFootprint() const override
	{
		return sizeof(*this) + GetAllocatedSize();
	}

	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override
	{
		FPrimitiveViewRelevance Result;
		Result.bDrawRelevance = IsShown(View);
		Result.bShadowRelevance = IsShadowCast(View);
		Result.bDynamicRelevance = true;
		Result.bRenderInMainPass = true;
		Result.bUsesLightingChannels = GetLightingChannelMask() != GetDefaultLightingChannelMask();
		Result.bRenderCustomDepth = ShouldRenderCustomDepth();
		Result.bTranslucentSelfShadow = CastsVolumetricTranslucentShadow();
		Result.bVelocityRelevance = IsMovable() && Result.bOpaque && Result.bRenderInMainPass;
		MaterialRelevance.SetPrimitiveViewRelevance(Result);
		return Result;
	}

	virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;

	/** Sets up a FMeshBatch for a specific LOD and element. */
	bool GetMeshElement(
		int32 LODIndex, 
		int32 BatchIndex, 
		int32 ElementIndex, 
		uint8 InDepthPriorityGroup, 
		FMeshBatch& OutMeshBatch) const;
	
private:

	FMaterialRelevance MaterialRelevance;

	FMyCustomVertexFactory VertexFactory;

	UStaticMesh* MyMesh;

	UCustomSkeletonMeshComponent* Component;
};
