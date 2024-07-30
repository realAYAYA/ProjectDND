#include "GM.h"
#include "DGameTypes.h"

void UDCheatManager::Sgm(const FString& Command)
{
	UE_LOG(LogProjectD, Log, TEXT("使用GM: %s"), *Command);

	auto Pc = GetPlayerController();
	if (!Pc->HasAuthority())
		return;

	TArray<FString> ParamStr;
	const int32 ParamNum = Command.ParseIntoArray(ParamStr, TEXT(" "));

	return;
}
