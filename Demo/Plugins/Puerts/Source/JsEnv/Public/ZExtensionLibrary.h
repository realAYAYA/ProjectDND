#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ZExtensionLibrary.generated.h"

class UWidget;

USTRUCT(BlueprintType)
struct JSENV_API FJsHeapStatistics
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="IdleZ")
	int64 TotalHeapSize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="IdleZ")
	int64 TotalHeapSizeExecutable = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="IdleZ")
	int64 TotalPhysicalSize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="IdleZ")
	int64 TotalAvailableSize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="IdleZ")
	int64 TotalGlobalHandlesSize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="IdleZ")
	int64 UsedGlobalHandlesSize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="IdleZ")
	int64 UsedHeapSize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="IdleZ")
	int64 HeapSizeLimit = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="IdleZ")
	int64 MallocedMemory = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="IdleZ")
	int64 ExternalMemory = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="IdleZ")
	int64 PeakMallocedMemory = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="IdleZ")
	int64 NumberOfNativeContexts = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="IdleZ")
	int64 NumberOfDetachedContexts = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="IdleZ")
	int64 DoesZapGarbage = 0;
};

UCLASS()
class JSENV_API UZExtensionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:	
	UFUNCTION(BlueprintCallable, Category = "PuertsExtension")
	static bool ZReadFile(FString Path, FString& Data);
	
	UFUNCTION(BlueprintCallable, Category = "PuertsExtension")
	static FString ZResolvePath(FString Path);

	UFUNCTION(BlueprintCallable, Category = "PuertsExtension")
	static bool ZFileExists(FString Path);

	UFUNCTION(BlueprintCallable, Category = "PuertsExtension")
	static bool ZDirectoryExists(FString Path);

	UFUNCTION(BlueprintCallable, Category = "PuertsExtension")
	static void ZCreateDirectory(FString Path);
	
	UFUNCTION(BlueprintCallable, Category = "PuertsExtension")
	static FString ZGetCurrentDirectory();

	UFUNCTION(BlueprintCallable, Category = "PuertsExtension")
	static TArray<FString> ZGetDirectories(FString Path);

	UFUNCTION(BlueprintCallable, Category = "PuertsExtension")
	static TArray<FString> ZGetFiles(FString Path);
	
	/*UFUNCTION(BlueprintCallable, Category = "PuertsExtension")
	static UObject* ZJsNewPermanentObject(UClass* Class);*/

	UFUNCTION(BlueprintCallable, Category = "PuertsExtension")
	static void ZJsReleasePermanentObject(UObject* Object);

	UFUNCTION(BlueprintCallable, Category = "PuertsExtension")
	static void ZClearJsPermanentObjects();	
	
	UFUNCTION(BlueprintCallable, Category = "PuertsExtension")
	static int32 ZGetJsPermanentObjectNum();	
	
	UFUNCTION(BlueprintCallable, Category = "PuertsExtension")
	static void ZGetAllWidgets(UUserWidget* InWidget, TArray<UWidget*>& OutWidgets);

	UFUNCTION(BlueprintCallable, Category = "PuertsExtension")
	static void ZGetAllUserWidgets(UUserWidget* InWidget, TArray<UUserWidget*>& OutWidgets);	

	UFUNCTION(BlueprintCallable, Category = "PuertsExtension")
	static FString ZGetObjectPathName(UObject* Object);

	/*UFUNCTION(BlueprintCallable, Category = "PuertsExtension")
	static void ZGetAllUserWidgetsByCDO(UClass* Class, TArray<UUserWidget*>& OutWidgets);*/
	
};
