#include "GameCounter.h"

void UGameplayCounter::AddToLayer1(const int32 Key, const int64 Num)
{
}

void UGameplayCounter::AddToLayer2(const int32 Key1, const int32 Key2, const int64 Num)
{
}

void UGameplayCounter::AddToLayer3(const int32 Key1, const int32 Key2, const int32 Key3, const int64 Num)
{
}

void UGameplayCounter::SetLayer1(const int32 Key, const int64 Num)
{
}

void UGameplayCounter::SetLayer2(const int32 Key1, const int32 Key2, const int64 Num)
{
}

void UGameplayCounter::SetLayer3(const int32 Key1, const int32 Key2, const int32 Key3, const int64 Num)
{
}

int64 UGameplayCounter::GetNumFromLayer1(const int32 Key)
{
	return 0;
}

int64 UGameplayCounter::GetNumFromLayer2(const int32 Key1, const int32 Key2)
{
	return 0;
}

int64 UGameplayCounter::GetNumFromLayer3(const int32 Key1, const int32 Key2, const int32 Key3)
{
	return 0;
}

bool UGameplayCounter::CheckNumFromLayer1(const int32 Key, const int64 Num)
{
	return false;
}

bool UGameplayCounter::CheckNumFromLayer2(const int32 Key1, const int32 Key2, const int64 Num)
{
	return false;
}

bool UGameplayCounter::CheckNumFromLayer3(const int32 Key1, const int32 Key2, const int32 Key3, const int64 Num)
{
	return false;
}

int64 UGameplayCounter::GetTotalNumFromLayer1()
{
	return 0;
}

int64 UGameplayCounter::GetTotalNumFromLayer2()
{
	return 0;
}

int64 UGameplayCounter::GetTotalNumFromLayer2WithKey(const int32 Key1)
{
	return 0;
}

int64 UGameplayCounter::GetTotalNumFromLayer3()
{
	return 0;
}

int64 UGameplayCounter::GetTotalNumFromLayer3WithOneKey(const int32 Key1)
{
	return 0;
}

int64 UGameplayCounter::GetTotalNumFromLayer3WithTwoKey(const int32 Key1, const int32 Key2)
{
	return 0;
}

bool UGameplayCounter::CheckTotalNumFromLayer1(const int64 Num)
{
	return false;
}

bool UGameplayCounter::CheckTotalNumFromLayer2(const int64 Num)
{
	return false;
}

bool UGameplayCounter::CheckTotalNumFromLayer2WithKey(const int32 Key1, const int64 Num)
{
	return false;
}

bool UGameplayCounter::CheckTotalNumFromLayer3(const int64 Num)
{
	return false;
}

bool UGameplayCounter::CheckTotalNumFromLayer3WithOneKey(const int32 Key1, const int64 Num)
{
	return false;
}

bool UGameplayCounter::CheckTotalNumFromLayer3WithTwoKey(const int32 Key1, const int32 Key2, const int64 Num)
{
	return false;
}