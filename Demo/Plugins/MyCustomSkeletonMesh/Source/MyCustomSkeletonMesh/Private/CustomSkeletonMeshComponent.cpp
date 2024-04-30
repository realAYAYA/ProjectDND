#include "CustomSkeletonMeshComponent.h"

#include "DataDrivenShaderPlatformInfo.h"
#include "MeshMaterialShader.h"
#include "MaterialDomain.h"
#include "Materials/MaterialRenderProxy.h"

void FMyCustomVertexFactory::ModifyCompilationEnvironment(const FVertexFactoryShaderPermutationParameters& Parameters,
                                                          FShaderCompilerEnvironment& OutEnvironment)
{
	OutEnvironment.SetDefine(TEXT("MANUAL_VERTEX_FETCH"), TEXT("0"));
	OutEnvironment.SetDefine(TEXT("MY_CUSTOM_MESH"), TEXT("1"));
}

bool FMyCustomVertexFactory::ShouldCompilePermutation(const FVertexFactoryShaderPermutationParameters& Parameters)
{
	if (Parameters.MaterialParameters.MaterialDomain == EMaterialDomain::MD_Surface &&
		Parameters.MaterialParameters.ShadingModels.IsUnlit())
		return true;

	return false;
}

void FMyCustomVertexFactory::InitRHI(FRHICommandListBase& RHICmdList)
{
	check(HasValidFeatureLevel());

	FVertexDeclarationElementList Elements;
	FVertexDeclarationElementList PosOnlyElements;

	if (Data.PositionComponent.VertexBuffer != nullptr)
	{
		Elements.Add(AccessStreamComponent(Data.PositionComponent, 0));
		Elements.Add(AccessStreamComponent(Data.PositionComponent, 1));// 绑定一份位移变换数据
		PosOnlyElements.Add(AccessStreamComponent(Data.PositionComponent, 0, EVertexInputStreamType::PositionOnly));
	}

	InitDeclaration(PosOnlyElements, EVertexInputStreamType::PositionOnly);

	if (Data.TextureCoordinates.Num())
	{
		constexpr int32 BaseTexCoordAttribute = 4;
		for (int32 i = 0; i < Data.TextureCoordinates.Num(); i++)
		{
			Elements.Add(AccessStreamComponent(Data.TextureCoordinates[i], BaseTexCoordAttribute + i));
		}

		for (int32 i = Data.TextureCoordinates.Num(); i < MAX_STATIC_TEXCOORDS / 2; i++)
		{
			Elements.Add(AccessStreamComponent(Data.TextureCoordinates.Last(), BaseTexCoordAttribute + i));
		}
	}

	check(Streams.Num() > 0);
	InitDeclaration(Elements);
	check(IsValidRef(GetDeclaration()))
}

void FMyCustomVertexFactory::Init(const FStaticMeshVertexBuffers* VertexBuffer)
{
	FLocalVertexFactory::FDataType NewData;
	VertexBuffer->PositionVertexBuffer.BindPositionVertexBuffer(this, NewData);
	VertexBuffer->StaticMeshVertexBuffer.BindPackedTexCoordVertexBuffer(this, NewData);
	SetData(NewData);

	if (!IsInitialized())
		InitResource(GetCommandList());
	else
		UpdateRHI(GetCommandList());
}

void FMyCustomVertexFactory::ReleaseRHI()
{
	FLocalVertexFactory::ReleaseRHI();
}

FPrimitiveSceneProxy* UCustomSkeletonMeshComponent::CreateSceneProxy()
{
	if (RHISupportsManualVertexFetch(GMaxRHIShaderPlatform))
		SceneProxy = new FMyCustomPrimitiveSceneProxy(this);

	return SceneProxy;
}

void FMyCustomPrimitiveSceneProxy::GetDynamicMeshElements(
	const TArray<const FSceneView*>& Views,
	const FSceneViewFamily& ViewFamily,
	uint32 VisibilityMap,
	FMeshElementCollector& Collector) const
{
	const bool bWireframe = AllowDebugViewmodes() && ViewFamily.EngineShowFlags.Wireframe;

	FColoredMaterialRenderProxy* WireframeMaterialInstance = nullptr;
	if (bWireframe)
	{
		WireframeMaterialInstance = new FColoredMaterialRenderProxy(
			GEngine->WireframeMaterial ? GEngine->WireframeMaterial->GetRenderProxy() : nullptr,
			FLinearColor(0.8f, 0.8f, 0));
		
		Collector.RegisterOneFrameMaterialProxy(WireframeMaterialInstance);
	}

	if (!MyMesh) return;

	const FStaticMeshRenderData* RenderData = MyMesh->GetRenderData();
	for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++)
	{
		const FSceneView* View = Views[ViewIndex];
		
		if (IsShown(View) && VisibilityMap & 1 << ViewIndex)
		{
			for (int32 LODIndex = 0; LODIndex < RenderData->LODResources.Num(); LODIndex++)
			{
				const FStaticMeshLODResources& LODModel = RenderData->LODResources[LODIndex];
				for (int32 SectionIndex = 0; SectionIndex < LODModel.Sections.Num(); SectionIndex++)
				{
					FMeshBatch& MeshElement = Collector.AllocateMesh();
					if (GetMeshElement(LODIndex, 1, SectionIndex, SDPG_World, MeshElement))
					{
						//if (MeshElement.bDitheredLODTransition && LODMask.IsDithered())
						{

						}
						//else
						{
							MeshElement.bDitheredLODTransition = false;
						}
								
						MeshElement.bCanApplyViewModeOverrides = true;
						//MeshElement.bUseWireframeSelectionColoring = bSectionIsSelected;

						Collector.AddMesh(ViewIndex, MeshElement);
					}
				}
			}
		}
	}
}

bool FMyCustomPrimitiveSceneProxy::GetMeshElement(
	int32 LODIndex,
	int32 BatchIndex,
	int32 ElementIndex,
	uint8 InDepthPriorityGroup,
	FMeshBatch& OutMeshBatch) const
{
	const FStaticMeshRenderData* RenderData = MyMesh->GetRenderData();
	const FStaticMeshLODResources& LOD = RenderData->LODResources[LODIndex];
	
	const UMaterialInterface* SectionMaterial = Component->GetMaterial(ElementIndex);
	if (SectionMaterial == nullptr)
		SectionMaterial = UMaterial::GetDefaultMaterial(EMaterialDomain::MD_Surface);
	const FMaterialRenderProxy* MaterialProxy = SectionMaterial->GetRenderProxy();
	
	FMeshBatchElement& MeshBatchElement = OutMeshBatch.Elements[0];

	MeshBatchElement.IndexBuffer = &LOD.IndexBuffer;
	OutMeshBatch.bWireframe = false;

	OutMeshBatch.VertexFactory = &VertexFactory;
	OutMeshBatch.MaterialRenderProxy = MaterialProxy;

	/*bool bHasPrecomputedVolumetricLightMap;
	FMatrix PreviousLocalToWorld;
	int32 SingleCaptureIndex;
	bool bOutPutVelocity;
	GetScene().GetPrimitiveUniformShaderParameters_RenderThread(
		GetPrimitiveSceneInfo(),
		bHasPrecomputedVolumetricLightMap,
		PreviousLocalToWorld,
		SingleCaptureIndex,
		bOutPutVelocity);

	FDynamicPrimitiveUniformBuffer& DynamicPrimitiveUniformBuffer = Collector.AllocateOneFrameResource<FDynamicPrimitiveUniformBuffer>();
	DynamicPrimitiveUniformBuffer.Set(
		GetLocalToWorld(),
		PreviousLocalToWorld,
		GetBounds(),
		GetLocalBounds(),
		true,
		bHasPrecomputedVolumetricLightMap,
		bOutPutVelocity);
	
	MeshBatchElement.PrimitiveUniformBufferResource = &DynamicPrimitiveUniformBuffer.UniformBuffer;
	MeshBatchElement.PrimitiveIdMode = PrimID_FromPrimitiveSceneInfo;*/

	MeshBatchElement.FirstIndex = 0;
	MeshBatchElement.NumPrimitives = LOD.IndexBuffer.GetNumIndices() / 3;
	MeshBatchElement.MinVertexIndex = 0;
	MeshBatchElement.MaxVertexIndex = LOD.VertexBuffers.PositionVertexBuffer.GetNumVertices() - 1;

	OutMeshBatch.ReverseCulling = IsLocalToWorldDeterminantNegative();
	OutMeshBatch.Type = PT_TriangleList;
	OutMeshBatch.DepthPriorityGroup = InDepthPriorityGroup;
	OutMeshBatch.bCanApplyViewModeOverrides = false;
	
	return true;
}


class FMyCustomVertexFactoryShaderParameters : public FVertexFactoryShaderParameters
{
	
	DECLARE_TYPE_LAYOUT(FMyCustomVertexFactoryShaderParameters, NonVirtual);
	
public:
	
	void Bind(const FShaderParameterMap& ParameterMap)
	{
		/* We bind our shader paramters to the paramtermap that will be used with it, the SPF_Optional flags tells the compiler that this paramter is optional*/
		/* Otherwise, the shader compiler will complain when this parameter is not present in the shader file*/

		//TransformIndex.Bind(ParameterMap, TEXT("DMTransformIndex"), SPF_Optional);
		//TransformsSRV.Bind(ParameterMap, TEXT("DMTransforms"), SPF_Optional);
	};

	void GetElementShaderBindings(
		const class FSceneInterface* Scene,
		const FSceneView* View,
		const class FMeshMaterialShader* Shader,
		const EVertexInputStreamType InputStreamType,
		ERHIFeatureLevel::Type FeatureLevel,
		const FVertexFactory* VertexFactory,
		const FMeshBatchElement& BatchElement,
		class FMeshDrawSingleShaderBindings& ShaderBindings,
		FVertexInputStreamArray& VertexStreams
	) const
	{
		if (BatchElement.bUserDataIsColorVertexBuffer)
		{
			const auto* LocalVertexFactory = static_cast<const FLocalVertexFactory*>(VertexFactory);
			FColorVertexBuffer* OverrideColorVertexBuffer = (FColorVertexBuffer*)BatchElement.UserData;
			check(OverrideColorVertexBuffer);

			if (!LocalVertexFactory->SupportsManualVertexFetch(FeatureLevel))
			{
				LocalVertexFactory->GetColorOverrideStream(OverrideColorVertexBuffer, VertexStreams);
			}
		}
		//const FDeformMeshVertexFactory* DeformMeshVertexFactory = ((FDeformMeshVertexFactory*)VertexFactory);

		/* Get the transform index from the vertex factory and pass it as the value for TransformIndex */
		//const uint32 Index = DeformMeshVertexFactory->TransformIndex;
		//ShaderBindings.Add(TransformIndex, Index);
		/* Get tHE SRV from the scen proxy and pass is as the value for TransformsSRV*/
		//ShaderBindings.Add(TransformsSRV, DeformMeshVertexFactory->SceneProxy->GetDeformTransformsSRV());
	};
private:
	//LAYOUT_FIELD(FShaderParameter, TransformIndex);
	//LAYOUT_FIELD(FShaderResourceParameter, TransformsSRV);

};

IMPLEMENT_TYPE_LAYOUT(FMyCustomVertexFactoryShaderParameters);

IMPLEMENT_VERTEX_FACTORY_PARAMETER_TYPE(FMyCustomVertexFactory, SF_Vertex, FMyCustomVertexFactoryShaderParameters);

IMPLEMENT_VERTEX_FACTORY_TYPE(FMyCustomVertexFactory, "/Plugin/CustomShaders/LocalVertexFactory.ush",
							  EVertexFactoryFlags::UsedWithMaterials |
							  EVertexFactoryFlags::SupportsDynamicLighting |
							  EVertexFactoryFlags::SupportsPositionOnly |
							  EVertexFactoryFlags::SupportsRayTracing |
							  EVertexFactoryFlags::SupportsPrimitiveIdStream)
