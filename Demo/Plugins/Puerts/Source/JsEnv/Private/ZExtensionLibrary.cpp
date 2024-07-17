#include "ZExtensionLibrary.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "HAL/PlatformFile.h"
#include "Misc/SecureHash.h"

#include "ObjectRetainer.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"

#if PLATFORM_WINDOWS
#	include "Windows/AllowWindowsPlatformTypes.h"
#	include <Windows.h>
#	include "Windows/HideWindowsPlatformTypes.h"
#endif // PLATFORM_WINDOWS


bool UZExtensionLibrary::ZReadFile(FString Path, FString& Data)
{
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    IFileHandle* FileHandle = PlatformFile.OpenRead(*Path);
    if (FileHandle)
    {
        int len = FileHandle->Size();
        TArray<uint8> Content;
        Content.Reset(len + 2);
        Content.AddUninitialized(len);
        const bool Success = FileHandle->Read(Content.GetData(), len);
        delete FileHandle;

        if (Success)
        {
            FFileHelper::BufferToString(Data, Content.GetData(), Content.Num());
        }

        return Success;
    }
    return false;
}

FString UZExtensionLibrary::ZResolvePath(FString Path)
{
    return IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*Path);
}

bool UZExtensionLibrary::ZFileExists(FString Path)
{
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    return PlatformFile.FileExists(*Path);
}

bool UZExtensionLibrary::ZDirectoryExists(FString Path)
{
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    return PlatformFile.DirectoryExists(*Path);
}

void UZExtensionLibrary::ZCreateDirectory(FString Path)
{
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    PlatformFile.CreateDirectory(*Path);
}

FString UZExtensionLibrary::ZGetCurrentDirectory()
{
    return FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
}

TArray<FString> UZExtensionLibrary::ZGetDirectories(FString Path)
{
    IFileManager& FileManager = IFileManager::Get();
    TArray<FString> Dirs;
    if (!Path.EndsWith(TEXT("/")))
        Path = Path + TEXT("/");
    Path = Path + "*";
    FileManager.FindFiles(Dirs, *Path, false, true);
    return Dirs;
}

TArray<FString> UZExtensionLibrary::ZGetFiles(FString Path)
{
    IFileManager& FileManager = IFileManager::Get();
    TArray<FString> Dirs;
    if (!Path.EndsWith(TEXT("/")))
        Path = Path + TEXT("/");
    Path = Path + "*";
    FileManager.FindFiles(Dirs, *Path, true, false);
    return Dirs;
}


puerts::FObjectRetainer& GetPermanentObjects()
{
	static puerts::FObjectRetainer PermanentObjects;
	return PermanentObjects;
}

/*
UObject* UZExtensionLibrary::ZJsNewPermanentObject(UClass* Class)
{
	UObject* Outer = GetTransientPackage();
	FName Name = NAME_None;
	EObjectFlags ObjectFlags = RF_NoFlags;
	UObject* Object = NewObject<UObject>(Outer, Class, Name, ObjectFlags);
	if (Object)
	{
		GetPermanentObjects().Retain(Object);
	}
	return Object;
}
*/

void UZExtensionLibrary::ZJsReleasePermanentObject(UObject* Object)
{
	if (Object)
	{
		GetPermanentObjects().Release(Object);
	}
}

void UZExtensionLibrary::ZClearJsPermanentObjects()
{
	GetPermanentObjects().Clear();
}

int32 UZExtensionLibrary::ZGetJsPermanentObjectNum()
{
	return GetPermanentObjects().Num();
}

void UZExtensionLibrary::ZGetAllWidgets(UUserWidget* InWidget, TArray<UWidget*>& OutWidgets)
{
	// 	InWidget->WidgetTree->GetAllWidgets(OutWidgets);
	InWidget->WidgetTree->ForEachWidget([&OutWidgets](UWidget* Widget)
	{
		OutWidgets.Add(Widget);
	});
}

void UZExtensionLibrary::ZGetAllUserWidgets(UUserWidget* InWidget, TArray<UUserWidget*>& OutWidgets)
{
	if (!InWidget || !InWidget->WidgetTree)
		return;
	
	InWidget->WidgetTree->ForEachWidget([&OutWidgets](UWidget* Widget)
	{
		if (auto* UserWidget = Cast<UUserWidget>(Widget))
		{
			OutWidgets.Add(UserWidget);
		}
	});	
}

FString UZExtensionLibrary::ZGetObjectPathName(UObject* Object)
{
	return GetPathNameSafe(Object);
}

/*
void UZExtensionLibrary::ZGetAllUserWidgetsByCDO(UClass* Class, TArray<UUserWidget*>& OutWidgets)
{
	if (!Class)
		return;
	if (auto* UserWidget = Cast<UUserWidget>(Class->ClassDefaultObject))
	{
		if (auto* OwningClass = UserWidget->GetWidgetTreeOwningClass())
		{
			OwningClass->GetWidgetTreeArchetype()->ForEachWidget([&OutWidgets](UWidget* Widget)
			{
				if (auto* UserWidget = Cast<UUserWidget>(Widget))
				{
					OutWidgets.Add(UserWidget);
				}
			});			
		}
		
		// ZGetAllUserWidgets(UserWidget->GetWidgetTreeOwningClass(), OutWidgets);
	}
}*/
