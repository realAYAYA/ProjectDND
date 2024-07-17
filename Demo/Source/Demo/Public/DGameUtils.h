#pragma once
#include "CoreMinimal.h"
#include "DGameUtils.generated.h"

USTRUCT(BlueprintType)
struct FIntArray2D
{
	GENERATED_USTRUCT_BODY()
	
	TArray<TArray<int32>> Matrix;

	FIntVector2 GetLength() const
	{
		FIntVector2 LW(0);
		LW.Y = Matrix.Num();
		LW.X = LW.Y == 0 ? 0 : Matrix[0].Num();
		return LW;
	}

	int32 Get(const int32 X, const int32 Y) const
	{
		if (Matrix.IsValidIndex(Y) && Matrix[Y].IsValidIndex(X))
			return Matrix[Y][X];

		return -1;
	}

	void Set(const int32 X, const int32 Y, const int32 Num)
	{
		if (Matrix.IsValidIndex(Y) && Matrix[Y].IsValidIndex(X))
			Matrix[Y][X] = Num;
	}

	void Reset(const int32 LengthX, const int32 LengthY)
	{
		Matrix.Empty();
		Matrix.SetNum(LengthY);
		for (auto& Row : Matrix)
			Row.Init(0, LengthX);
	}

	// 检测是否可以将一个给定Size和Pos的地块完成塞入，并返回塞入过程中的具体情况
	bool OverlapTest(const FIntVector2 BeginPos, const FIntVector2 Size, TArray<FIntVector>& HitResult) const
	{
		bool bOk = true;
		for (int32 Y = BeginPos.Y; Y < Size.Y; Y++)
		{
			for (int32 X = BeginPos.X; X < Size.X; X++)
			{
				const int32 Value = Get(X, Y);
				if (Value != 0)
					bOk = false;

				HitResult.Add(FIntVector(X, Y, Value));
			}
		}

		return bOk;
	}

	// 快速检测是否可以将一个给定Size和Pos的地块完成塞入
	bool OverlapTestFast(const FIntVector2 BeginPos, const FIntVector2 Size) const
	{
		for (int32 Y = BeginPos.Y; Y < Size.Y; Y++)
		{
			for (int32 X = BeginPos.X; X < Size.X; X++)
			{
				const int32 Value = Get(X, Y);
				if (Value != 0)
					return false;
			}
		}
		
		return true;
	}

	void DoOverlap(const FIntVector2 BeginPos, const FIntVector2 Size, const int32 Value)
	{
		for (int32 Y = BeginPos.Y; Y < Size.Y; Y++)
		{
			for (int32 X = BeginPos.X; X < Size.X; X++)
			{
				Set(X, Y, Value);
			}
		}
	}

	void SetWithValue(const int32 OldValue, const int32 NewValue)
	{
		const auto LW = GetLength();
		for (int32 Y = 0; Y < LW.Y; Y++)
		{
			for (int32 X = 0; X < LW.X; X++)
			{
				if (Get(X, Y) == OldValue)
					Set(X, Y, NewValue);
			}
		}
	}
};
