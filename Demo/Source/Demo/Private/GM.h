#pragma once
#include "GameFramework/CheatManager.h"
#include "GM.generated.h"

UCLASS()
class UDCheatManager : public UCheatManager
{
	GENERATED_BODY()

public:

	// 服务器gm
	UFUNCTION(Exec)
	void Sgm(const FString& Command);
};
