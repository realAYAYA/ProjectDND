#pragma once

#include "CoreMinimal.h"
#include "DGameDefine.generated.h"

class UGameplayAbility;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EMBuffType : uint8
{
	None		UMETA(Displayname = "None"),	// 用于无法被驱散的效果
	Spell		UMETA(Displayname = "Spell"),
	Combat		UMETA(Displayname = "Combat"),
};

UENUM(BlueprintType)
enum class EDDamageType : uint8
{
	Physical	UMETA(Displayname = "Physical"),
	Frost		UMETA(Displayname = "Frost"),
	Flame		UMETA(Displayname = "Flame"),
	Nature		UMETA(Displayname = "Nature"),
	Divine		UMETA(Displayname = "Divine"),
	Shadow		UMETA(Displayname = "Shadow"),
	Chaos		UMETA(Displayname = "Chaos"),
};

USTRUCT(BlueprintType)
struct FDCharacterGasData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = GAS)
	TArray<TSubclassOf<UGameplayEffect>> Effects;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = GAS)
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;
	
};

UCLASS()
class UDCharacterDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly)
	FDCharacterGasData GasData;
};
