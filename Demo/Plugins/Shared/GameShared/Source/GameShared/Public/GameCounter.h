#pragma once
#include "CoreMinimal.h"
#include "GameCounter.generated.h"

// 单层计数器
USTRUCT()
struct GAMESHARED_API FCounterLayer1
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TMap<int32, int64> Map;

	void Add(const int32 Key, const int64 Num)
	{
		if (Map.Contains(Key))
			*Map.Find(Num) += Num;
		else
		{
			Map.Add(Key, Num);
		}
	}

	void Set(const int32 Key, const int64 Num)
	{
		if (Map.Contains(Key))
			*Map.Find(Num) = Num;
		else
		{
			Map.Add(Key, Num);
		}
	}
};

// 2层计数器
USTRUCT()
struct GAMESHARED_API FCounterLayer2
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TMap<int32, FCounterLayer1> Map;

	void Add(const int32 Key1, const int32 Key2, const int64 Num)
	{
		if (Map.Contains(Key1))
			Map.Find(Key1)->Add(Key2, Num);
		else
		{
			Map.Add(Key1).Add(Key2, Num);
		}
	}

	void Set(const int32 Key1, const int32 Key2, const int64 Num)
	{
		if (Map.Contains(Key1))
			Map.Find(Key1)->Set(Key2, Num);
		else
		{
			Map.Add(Key1).Add(Key2, Num);
		}
	}
};

// 3层计数器
USTRUCT()
struct GAMESHARED_API FGameplayCounterLayer3
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TMap<int32, FCounterLayer2> Map;

	void Add(const int32 Key1, const int32 Key2, const int32 Key3, const int64 Num)
	{
		if (Map.Contains(Key1))
			Map.Find(Key1)->Add(Key2, Key3, Num);
		else
		{
			Map.Add(Key1).Add(Key2, Key3, Num);
		}
	}
};

// 游戏计数器
UCLASS()
class GAMESHARED_API UGameplayCounter : public UObject
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "GameShared")
	void AddToLayer1(const int32 Key, const int64 Num);
	
	UFUNCTION(BlueprintCallable, Category = "GameShared")
	void AddToLayer2(const int32 Key1, const int32 Key2, const int64 Num);

	UFUNCTION(BlueprintCallable, Category = "GameShared")
	void AddToLayer3(const int32 Key1, const int32 Key2, const int32 Key3, const int64 Num);

	UFUNCTION(BlueprintCallable, Category = "GameShared")
	void SetLayer1(const int32 Key, const int64 Num);
	
	UFUNCTION(BlueprintCallable, Category = "GameShared")
	void SetLayer2(const int32 Key1, const int32 Key2, const int64 Num);

	UFUNCTION(BlueprintCallable, Category = "GameShared")
	void SetLayer3(const int32 Key1, const int32 Key2, const int32 Key3, const int64 Num);
	
	UFUNCTION(BlueprintCallable, Category = "GameShared")
	int64 GetNumFromLayer1(const int32 Key);
	
	UFUNCTION(BlueprintCallable, Category = "GameShared")
	int64 GetNumFromLayer2(const int32 Key1, const int32 Key2);

	UFUNCTION(BlueprintCallable, Category = "GameShared")
	int64 GetNumFromLayer3(const int32 Key1, const int32 Key2, const int32 Key3);

	UFUNCTION(BlueprintCallable, Category = "GameShared")
	bool CheckNumFromLayer1(const int32 Key, const int64 Num);

	UFUNCTION(BlueprintCallable, Category = "GameShared")
	bool CheckNumFromLayer2(const int32 Key1, const int32 Key2, const int64 Num);

	UFUNCTION(BlueprintCallable, Category = "GameShared")
	bool CheckNumFromLayer3(const int32 Key1, const int32 Key2, const int32 Key3, const int64 Num);

	UFUNCTION(BlueprintCallable, Category = "GameShared")
	int64 GetTotalNumFromLayer1();

	UFUNCTION(BlueprintCallable, Category = "GameShared")
	int64 GetTotalNumFromLayer2();

	UFUNCTION(BlueprintCallable, Category = "GameShared")
	int64 GetTotalNumFromLayer2WithKey(const int32 Key1);
	
	UFUNCTION(BlueprintCallable, Category = "GameShared")
	int64 GetTotalNumFromLayer3();

	UFUNCTION(BlueprintCallable, Category = "GameShared")
	int64 GetTotalNumFromLayer3WithOneKey(const int32 Key1);
	
	UFUNCTION(BlueprintCallable, Category = "GameShared")
	int64 GetTotalNumFromLayer3WithTwoKey(const int32 Key1, const int32 Key2);
	
	UFUNCTION(BlueprintCallable, Category = "GameShared")
	bool CheckTotalNumFromLayer1(const int64 Num);

	UFUNCTION(BlueprintCallable, Category = "GameShared")
	bool CheckTotalNumFromLayer2(const int64 Num);

	UFUNCTION(BlueprintCallable, Category = "GameShared")
	bool CheckTotalNumFromLayer2WithKey(const int32 Key1, const int64 Num);

	UFUNCTION(BlueprintCallable, Category = "GameShared")
	bool CheckTotalNumFromLayer3(const int64 Num);

	UFUNCTION(BlueprintCallable, Category = "GameShared")
	bool CheckTotalNumFromLayer3WithOneKey(const int32 Key1, const int64 Num);

	UFUNCTION(BlueprintCallable, Category = "GameShared")
	bool CheckTotalNumFromLayer3WithTwoKey(const int32 Key1, const int32 Key2, const int64 Num);

protected:

	UPROPERTY()
	FCounterLayer1 CounterLayer1;

	UPROPERTY()
	FCounterLayer2 CounterLayer2;

	UPROPERTY()
	FGameplayCounterLayer3 CounterLayer3;
};