// Copyright Epic Games, Inc. All Rights Reserved.

#include "FriesLibraryBPLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "GameFramework/GameUserSettings.h"
#include "RHIDefinitions.h"
#include "Kismet/GameplayStatics.h"
#include "OverallScalability.h"

// Plugin includes (this includes just need to plugin compile correctly)
#include "Misc/ConfigCacheIni.h"
#include "GameFramework/Pawn.h"

/*
Welcome to Fries Library, here you can find some functions that can help in the development of your project.
This plugin was originally designed for Unreal Engine 5.1.1, although over time I will update with new functions
or for new versions of Unreal Engine.
*/

// Function library base function
UFriesLibraryBPLibrary::UFriesLibraryBPLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

// Development Functions (Ex: Print with different variables)

void UFriesLibraryBPLibrary::PrintStringWithTell(const UObject* WorldContextObject, const FString InString /*= TEXT("Hello")*/, const bool bPrintToScreen /*= true*/, const bool bPrintToLog /*= true*/, const FLinearColor TextColor /*= FLinearColor(0.5, 0.0, 1.0)*/, const float Duration /*= 2.f*/, const FName Key /*= NAME_None*/)
{
	// Create string to print
	FString StringToPrint;
	StringToPrint += WorldContextObject->GetClass()->GetName();
	StringToPrint += TEXT(":   ");
	StringToPrint += InString;

	// Print string
	UKismetSystemLibrary::PrintString(WorldContextObject, StringToPrint, bPrintToScreen, bPrintToLog, TextColor, Duration, Key);
}

void UFriesLibraryBPLibrary::PrintBoolean(const UObject* WorldContextObject, const bool bInBoolean, const float Duration, const bool bPrintFunctionOwner, const bool bPrintToScreen, const bool bPrintToLog, const FLinearColor TextColor, const FName Key)
{
	if (bPrintFunctionOwner)
	{
		PrintStringWithTell(WorldContextObject, LexToString(bInBoolean), bPrintToScreen, bPrintToLog, TextColor, Duration, Key);
	}
	else
	{
		UKismetSystemLibrary::PrintString(WorldContextObject, LexToString(bInBoolean), bPrintToScreen, bPrintToLog, TextColor, Duration, Key);
	}
}

void UFriesLibraryBPLibrary::PrintInteger(const UObject* WorldContextObject, const int32 IntegerValue, const float Duration, const bool bPrintFunctionOwner, const bool bPrintToScreen, const bool bPrintToLog, const FLinearColor TextColor, const FName Key)
{
	if (bPrintFunctionOwner)
	{
		PrintStringWithTell(WorldContextObject, LexToString(IntegerValue), bPrintToScreen, bPrintToLog, TextColor, Duration, Key);
	}
	else
	{
		UKismetSystemLibrary::PrintString(WorldContextObject, LexToString(IntegerValue), bPrintToScreen, bPrintToLog, TextColor, Duration, Key);
	}
}

void UFriesLibraryBPLibrary::PrintFloat(const UObject* WorldContextObject, const float FloatValue, const float Duration, const bool bPrintFunctionOwner, const bool bPrintToScreen, const bool bPrintToLog, const FLinearColor TextColor, const FName Key)
{
	if (bPrintFunctionOwner)
	{
		PrintStringWithTell(WorldContextObject, FString::SanitizeFloat(FloatValue), bPrintToScreen, bPrintToLog, TextColor, Duration, Key);
	}
	else
	{
		UKismetSystemLibrary::PrintString(WorldContextObject, FString::SanitizeFloat(FloatValue), bPrintToScreen, bPrintToLog, TextColor, Duration, Key);
	}
}

void UFriesLibraryBPLibrary::PrintName(const UObject* WorldContextObject, const FName InName /*= NAME_None*/, const float Duration /*= 2.f*/, const bool bPrintFunctionOwner, const bool bPrintToScreen /*= true*/, const bool bPrintToLog /*= true*/, const FLinearColor TextColor /*= FLinearColor(1.0, 0.0, 0.0)*/, const FName Key /*= NAME_None*/)
{
	if (bPrintFunctionOwner)
	{
		PrintStringWithTell(WorldContextObject, LexToString(InName), bPrintToScreen, bPrintToLog, TextColor, Duration, Key);
	}
	else
	{
		UKismetSystemLibrary::PrintString(WorldContextObject, LexToString(InName), bPrintToScreen, bPrintToLog, TextColor, Duration, Key);
	}
}

void UFriesLibraryBPLibrary::PrintVector(const UObject* WorldContextObject, const FVector VectorValue /*= FVector(0.f, 0.f, 0.f)*/, const float Duration /*= 2.f*/, const bool bPrintFunctionOwner, const bool bPrintToScreen /*= true*/, const bool bPrintToLog /*= true*/, const FLinearColor TextColor /*= FLinearColor(1.0, 0.0, 0.0)*/, const FName Key /*= NAME_None*/)
{
	if (bPrintFunctionOwner)
	{
		PrintStringWithTell(WorldContextObject, UKismetStringLibrary::Conv_VectorToString(VectorValue), bPrintToScreen, bPrintToLog, TextColor, Duration, Key);
	}
	else
	{
		UKismetSystemLibrary::PrintString(WorldContextObject, UKismetStringLibrary::Conv_VectorToString(VectorValue), bPrintToScreen, bPrintToLog, TextColor, Duration, Key);
	}
}

void UFriesLibraryBPLibrary::PrintRotator(const UObject* WorldContextObject, const FRotator RotatorValue /*= FRotator(0.f, 0.f, 0.f)*/, const float Duration /*= 2.f*/, const bool bPrintFunctionOwner, const bool bPrintToScreen /*= true*/, const bool bPrintToLog /*= true*/, const FLinearColor TextColor /*= FLinearColor(1.0, 0.0, 0.0)*/, const FName Key /*= NAME_None*/)
{
	if (bPrintFunctionOwner)
	{
		PrintStringWithTell(WorldContextObject, UKismetStringLibrary::Conv_RotatorToString(RotatorValue), bPrintToScreen, bPrintToLog, TextColor, Duration, Key);
	}
	else
	{
		UKismetSystemLibrary::PrintString(WorldContextObject, UKismetStringLibrary::Conv_RotatorToString(RotatorValue), bPrintToScreen, bPrintToLog, TextColor, Duration, Key);
	}
}

void UFriesLibraryBPLibrary::PrintTransform(const UObject* WorldContextObject, const FTransform& TransformValue /*= FRotator(0.f, 0.f, 0.f)*/, const float Duration /*= 2.f*/, const bool bPrintFunctionOwner, const bool bPrintToScreen /*= true*/, const bool bPrintToLog /*= true*/, const FLinearColor TextColor /*= FLinearColor(1.0, 0.0, 0.0)*/, const FName Key /*= NAME_None*/)
{
	if (bPrintFunctionOwner)
	{
		PrintStringWithTell(WorldContextObject, UKismetStringLibrary::Conv_TransformToString(TransformValue), bPrintToScreen, bPrintToLog, TextColor, Duration, Key);
	}
	else
	{
		UKismetSystemLibrary::PrintString(WorldContextObject, UKismetStringLibrary::Conv_TransformToString(TransformValue), bPrintToScreen, bPrintToLog, TextColor, Duration, Key);
	}
}

void UFriesLibraryBPLibrary::PrintObject(const UObject* WorldContextObject, const UObject* Object, const float Duration /*= 2.f*/, const bool bPrintFunctionOwner, const bool bPrintToScreen /*= true*/, const bool bPrintToLog /*= true*/, const bool bPrintIfInvalid, const FLinearColor TextColor /*= FLinearColor(1.0, 0.0, 0.0)*/, const FName Key /*= NAME_None*/)
{
	// Verify is object is valid
	if (Object)
	{
		if (bPrintFunctionOwner)
		{
			PrintStringWithTell(WorldContextObject, Object->GetName(), bPrintToScreen, bPrintToLog, TextColor, Duration, Key);
		}
		else
		{
			UKismetSystemLibrary::PrintString(WorldContextObject, Object->GetName(), bPrintToScreen, bPrintToLog, TextColor, Duration, Key);
		}
	}
	// Print invalid if object is invalid
	else if (bPrintFunctionOwner && bPrintIfInvalid)
	{
		PrintStringWithTell(WorldContextObject, TEXT("Invalid"), bPrintToScreen, bPrintToLog, FLinearColor(1.0, 0.0, 0.0), Duration, Key);
	}
	else if (bPrintIfInvalid)
	{
		UKismetSystemLibrary::PrintString(WorldContextObject, TEXT("Invalid"), bPrintToScreen, bPrintToLog, FLinearColor(1.0, 0.0, 0.0), Duration, Key);
	}
}

// Random Things that can help you

FString UFriesLibraryBPLibrary::RandomLetter(const bool bToUpper)
{
	// Make array with each letter
	TArray<FString> Letters = { TEXT("A"), TEXT("B"), TEXT("C"), TEXT("D"), TEXT("E"), TEXT("F"), TEXT("G"), TEXT("H"), TEXT("I"),
	TEXT("J"), TEXT("K"), TEXT("L"), TEXT("M"), TEXT("N"), TEXT("O"), TEXT("P"), TEXT("Q"), TEXT("R"), TEXT("S"), TEXT("T"), TEXT("U"), 
	TEXT("V"), TEXT("W"), TEXT("X"), TEXT("Y"), TEXT("Z")};
	
	// Get random letter
	const int32 RandIndex = FMath::RandRange(0, Letters.Num() - 1);

	// Check if it's lowercase or uppercase
	return bToUpper ? Letters[RandIndex] : Letters[RandIndex].ToLower();
}

FString UFriesLibraryBPLibrary::RandomLetterInRange(int32 Min, int32 Max, const bool bToUpper)
{
	// Verify if the Max value are big (> 26)
	if (Max > 25 || Max < 1)
	{
		Max = 25;
	}

	// Verify if the Min value are small (< 0)
	if (Min < 0 || Min > 24)
	{
		Min = 0;
	}

	// Make array with each letter
	TArray<FString> Letters = { TEXT("A"), TEXT("B"), TEXT("C"), TEXT("D"), TEXT("E"), TEXT("F"), TEXT("G"), TEXT("H"), TEXT("I"),
	TEXT("J"), TEXT("K"), TEXT("L"), TEXT("M"), TEXT("N"), TEXT("O"), TEXT("P"), TEXT("Q"), TEXT("R"), TEXT("S"), TEXT("T"), TEXT("U"),
	TEXT("V"), TEXT("W"), TEXT("X"), TEXT("Y"), TEXT("Z") };

	// Get random letter
	const int32 RandIndex = FMath::RandRange(Min, Max);

	// Check if it's lowercase or uppercase
	return bToUpper ? Letters[RandIndex].ToUpper() : Letters[RandIndex].ToLower();
}

/* Deprecated function */
bool UFriesLibraryBPLibrary::IsAIControlled(const APawn* Target)
{
	/* old code
		// Verify if Target Is Valid
		if (Target)
		{
			// Verify if AI Controller Is Valid
			if (Target->GetController())
			{
				// Verify if Target is not locally controlled
				return !Target->IsLocallyControlled();
			}
			return false;
		}
	*/

	// new code
	return Target->IsBotControlled();
}

// Additional Functions to modify user settings

void UFriesLibraryBPLibrary::SaveGameUserSettings()
{
	// Get game user settings ref
	UGameUserSettings* GameUserSettings = UGameUserSettings::GetGameUserSettings();
	// Apply Settings
	GameUserSettings->ApplyResolutionSettings(true);
	GameUserSettings->ApplySettings(true);
	GameUserSettings->SaveSettings();
}

EFlEngineScalabilityLevel UFriesLibraryBPLibrary::GetScalabilityLevel(const EFlEngineScalabilityType ScalabilityToGet)
{
	// Declare level variable, is modified later
	int Level = 0;

	// Get game user settings ref
	const UGameUserSettings* GameUserSettings = UGameUserSettings::GetGameUserSettings();

	// Apply scalability level by scalability type
	switch (ScalabilityToGet)
	{
	case EFlEngineScalabilityType::Overall:
		Level = GameUserSettings->GetOverallScalabilityLevel();
		break;
	case EFlEngineScalabilityType::ViewDistance:
		Level = GameUserSettings->GetViewDistanceQuality();
		break;
	case EFlEngineScalabilityType::AntiAliasing:
		Level = GameUserSettings->GetAntiAliasingQuality();
		break;
	case EFlEngineScalabilityType::PostProcessing:
		Level = GameUserSettings->GetPostProcessingQuality();
		break;
	case EFlEngineScalabilityType::Shadows:
		Level = GameUserSettings->GetShadowQuality();
		break;
	case EFlEngineScalabilityType::GlobalIllumination:
		Level = GameUserSettings->GetGlobalIlluminationQuality();
		break;
	case EFlEngineScalabilityType::Reflections:
		Level = GameUserSettings->GetReflectionQuality();
		break;
	case EFlEngineScalabilityType::Textures:
		Level = GameUserSettings->GetTextureQuality();
		break;
	case EFlEngineScalabilityType::Effects:
		Level = GameUserSettings->GetVisualEffectQuality();
		break;
	case EFlEngineScalabilityType::Foliage:
		Level = GameUserSettings->GetFoliageQuality();
		break;
	case EFlEngineScalabilityType::Shading:
		Level = GameUserSettings->GetShadingQuality();
		break;
	}
	return static_cast<EFlEngineScalabilityLevel>(Level);
}

void UFriesLibraryBPLibrary::ModifyScalability(const EFlEngineScalabilityType ScalabilityToModify, const EFlEngineScalabilityLevel NewScalabilityLevel, const bool bSaveInConfig)
{
	// Convert level byte to int32
	const int Level = static_cast<int>(NewScalabilityLevel);

	// Get game user settings ref
	UGameUserSettings* GameUserSettings = UGameUserSettings::GetGameUserSettings();

	// Apply scalability level by scalability type
	switch (ScalabilityToModify)
	{
		case EFlEngineScalabilityType::Overall:
			GameUserSettings->SetOverallScalabilityLevel(Level);
			break;
		case EFlEngineScalabilityType::ViewDistance:
			GameUserSettings->SetViewDistanceQuality(Level);
			break;
		case EFlEngineScalabilityType::AntiAliasing:
			GameUserSettings->SetAntiAliasingQuality(Level);
			break;
		case EFlEngineScalabilityType::PostProcessing:
			GameUserSettings->SetPostProcessingQuality(Level);
			break;
		case EFlEngineScalabilityType::Shadows:
			GameUserSettings->SetShadowQuality(Level);
			break;
		case EFlEngineScalabilityType::GlobalIllumination:
			GameUserSettings->SetGlobalIlluminationQuality(Level);
			break;
		case EFlEngineScalabilityType::Reflections:
			GameUserSettings->SetReflectionQuality(Level);
			break;
		case EFlEngineScalabilityType::Textures:
			GameUserSettings->SetTextureQuality(Level);
			break;
		case EFlEngineScalabilityType::Effects:
			GameUserSettings->SetVisualEffectQuality(Level);
			break;
		case EFlEngineScalabilityType::Foliage:
			GameUserSettings->SetFoliageQuality(Level);
			break;
		case EFlEngineScalabilityType::Shading:
			GameUserSettings->SetShadingQuality(Level);
			break;
	}
	if (bSaveInConfig)
	{
		// Save new scalability
		SaveGameUserSettings();
	}
}

void UFriesLibraryBPLibrary::SetOverallScalability(const UOverallScalability* OverallData, const EFlEngineScalabilityLevel NewScalabilityLevel)
{
	// Verify if data asset is valid
	if (OverallData)
	{
		// Set all scalability types by data asset
		ModifyScalability(EFlEngineScalabilityType::AntiAliasing, OverallData->ScalabilityInfo.AntiAliasing, false);
		ModifyScalability(EFlEngineScalabilityType::Effects, OverallData->ScalabilityInfo.Effects, false);
		ModifyScalability(EFlEngineScalabilityType::Foliage, OverallData->ScalabilityInfo.Foliage, false);
		ModifyScalability(EFlEngineScalabilityType::GlobalIllumination, OverallData->ScalabilityInfo.GlobalIllumination, false);
		ModifyScalability(EFlEngineScalabilityType::PostProcessing, OverallData->ScalabilityInfo.PostProcessing, false);
		ModifyScalability(EFlEngineScalabilityType::Reflections, OverallData->ScalabilityInfo.Reflections, false);
		ModifyScalability(EFlEngineScalabilityType::Shading, OverallData->ScalabilityInfo.Shading, false);
		ModifyScalability(EFlEngineScalabilityType::Shadows, OverallData->ScalabilityInfo.Shadows, false);
		ModifyScalability(EFlEngineScalabilityType::Textures, OverallData->ScalabilityInfo.Textures, false);
		ModifyScalability(EFlEngineScalabilityType::ViewDistance, OverallData->ScalabilityInfo.ViewDistance, false);

		// Save new scalability
		SaveGameUserSettings();
	}
	else
	{
		// Set all scalability types by level
		ModifyScalability(EFlEngineScalabilityType::Overall, NewScalabilityLevel, true);
	}
}

EFlAmbientOcclusion UFriesLibraryBPLibrary::GetAmbientOcclusion()
{
	// Verify if r.AmbientOcclusion.Method is = 0 (0 = SSAO)
	if (UKismetSystemLibrary::GetConsoleVariableIntValue("r.AmbientOcclusion.Method") == 0)
	{
		return EFlAmbientOcclusion::SSAO;
	}
	return EFlAmbientOcclusion::GTAO;
}

void UFriesLibraryBPLibrary::SetAmbientOcclusion(const UObject* WorldContextObject, const EFlAmbientOcclusion NewAmbientOcclusion, const bool bSaveInConfig)
{
	// Select console command by ambient occlusion enum
	switch (NewAmbientOcclusion)
	{
	case EFlAmbientOcclusion::SSAO:
		// Set ambient occlusion in SSAO (0 = SSAO)
		UKismetSystemLibrary::ExecuteConsoleCommand(WorldContextObject, "r.AmbientOcclusion.Method 0");
		break;
	case EFlAmbientOcclusion::GTAO:
		// Set ambient occlusion in GTAO (1 = GTAO)
		UKismetSystemLibrary::ExecuteConsoleCommand(WorldContextObject, "r.AmbientOcclusion.Method 1");
		break;

	}
	// Save new ambient occlusion in user config 
	if (bSaveInConfig)
	{
		SaveGameUserSettings();
	}
}

EFlAntiAliasingMethod UFriesLibraryBPLibrary::GetAntiAliasingMethod()
{
	// Find current anti-aliasing method by r.AntiAliasingMethod
	switch (UKismetSystemLibrary::GetConsoleVariableIntValue("r.AntiAliasingMethod"))
	{
		default:
			return EFlAntiAliasingMethod::None;
		case 0:
			return EFlAntiAliasingMethod::None;
		case 1:
			return EFlAntiAliasingMethod::FXAA;
		case 2:
			return EFlAntiAliasingMethod::TAA;
		case 3:
			return EFlAntiAliasingMethod::MSAA;
		case 4:
			return EFlAntiAliasingMethod::TSR;
	}
}

EFlGlobalIlluminationMethod UFriesLibraryBPLibrary::GetGlobalIllumination()
{
	// Find current global illumination by r.DynamicGlobalIlluminationMethod
	switch (UKismetSystemLibrary::GetConsoleVariableIntValue("r.DynamicGlobalIlluminationMethod"))
	{
	default:
		return EFlGlobalIlluminationMethod::None;
	case 0:
		return EFlGlobalIlluminationMethod::None;
	case 1:
		return EFlGlobalIlluminationMethod::Lumen;
	case 2:
		return EFlGlobalIlluminationMethod::SSGI;
	case 3:
		return EFlGlobalIlluminationMethod::RTGI;
	case 4:
		return EFlGlobalIlluminationMethod::Plugin;
	}
}

void UFriesLibraryBPLibrary::SetAntiAliasingMethod(const UObject* WorldContextObject, const EFlAntiAliasingMethod NewAntiAliasingMethod, const bool bSaveInConfig)
{
	// Select console command by anti-aliasing enum
	switch (NewAntiAliasingMethod)
	{
		case EFlAntiAliasingMethod::None:
			// Set anti-aliasing in None (0 = None)
			UKismetSystemLibrary::ExecuteConsoleCommand(WorldContextObject, "r.AntiAliasingMethod 0");
			break;
		case EFlAntiAliasingMethod::FXAA:
			// Set anti-aliasing in FXAA (1 = FXAA)
			UKismetSystemLibrary::ExecuteConsoleCommand(WorldContextObject, "r.AntiAliasingMethod 1");
			break;
		case EFlAntiAliasingMethod::MSAA:
			// Set anti-aliasing in MSAA (2 = MSAA)
			UKismetSystemLibrary::ExecuteConsoleCommand(WorldContextObject, "r.AntiAliasingMethod 2");
			break;
		case EFlAntiAliasingMethod::TAA:
			// Set anti-aliasing in TAA (3 = TAA)
			UKismetSystemLibrary::ExecuteConsoleCommand(WorldContextObject, "r.AntiAliasingMethod 3");
			break;
		case EFlAntiAliasingMethod::TSR:
			// Set anti-aliasing in TSR (4 = TSR)
			UKismetSystemLibrary::ExecuteConsoleCommand(WorldContextObject, "r.AntiAliasingMethod 4");
			break;
	}
	// Save new anti-aliasing in user config 
	if (bSaveInConfig)
	{
		SaveGameUserSettings();
	}
}

void UFriesLibraryBPLibrary::SetGlobalIlluminationMethod(const UObject* WorldContextObject,
	const EFlGlobalIlluminationMethod NewGlobalIllumination, const bool bSaveInConfig)
{
	// Select console command by global illumination enum
	switch (NewGlobalIllumination)
	{
		case EFlGlobalIlluminationMethod::None:
			UKismetSystemLibrary::ExecuteConsoleCommand(WorldContextObject, "r.DynamicGlobalIlluminationMethod 0");
			break;
		case EFlGlobalIlluminationMethod::Lumen:
			UKismetSystemLibrary::ExecuteConsoleCommand(WorldContextObject, "r.DynamicGlobalIlluminationMethod 1");
			break;
		case EFlGlobalIlluminationMethod::SSGI:
			UKismetSystemLibrary::ExecuteConsoleCommand(WorldContextObject, "r.DynamicGlobalIlluminationMethod 2");
			break;
		case EFlGlobalIlluminationMethod::RTGI:
			UKismetSystemLibrary::ExecuteConsoleCommand(WorldContextObject, "r.DynamicGlobalIlluminationMethod 3");
			break;
		case EFlGlobalIlluminationMethod::Plugin:
			UKismetSystemLibrary::ExecuteConsoleCommand(WorldContextObject, "r.DynamicGlobalIlluminationMethod 4");
			break;
	}
	
	// Save new anti-aliasing in user config 
	if (bSaveInConfig)
	{
		SaveGameUserSettings();
	}
}

// RHI Functions

void UFriesLibraryBPLibrary::SetGraphicsRHI(const EGraphicsRHI GraphicsRHI)
{
	// Get current platform
	const FString TargetPlataform = UGameplayStatics::GetPlatformName();

	// Set string variables to apply later
	const FString RHI_DX11(TEXT("DefaultGraphicsRHI_DX11"));
	const FString RHI_DX12(TEXT("DefaultGraphicsRHI_DX12"));
	const FString RHI_Vulkan(TEXT("DefaultGraphicsRHI_Vulkan"));

	// This code just valid for Windows, sorry
	if (TargetPlataform == "Windows")
	{
		FString DefaultGraphicsRHI;
		// Set current RHI in GConfig
		GConfig->GetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), DefaultGraphicsRHI, GEngineIni);
		switch (GraphicsRHI)
		{
		case EGraphicsRHI::RHI_DX11:
			if (DefaultGraphicsRHI != "DefaultGraphicsRHI_DX11")
			{
				GConfig->SetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), *RHI_DX11, GEngineIni);
				GConfig->Flush(true, GEngineIni);
				return;
			}
			return;

		case EGraphicsRHI::RHI_DX12:
			if (DefaultGraphicsRHI != "DefaultGraphicsRHI_DX12")
			{
				GConfig->SetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), *RHI_DX12, GEngineIni);
				GConfig->Flush(true, GEngineIni);
				return;
			}
			return;

		case EGraphicsRHI::RHI_Vulkan:
			if (DefaultGraphicsRHI != "DefaultGraphicsRHI_Vulkan")
			{
				GConfig->SetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), *RHI_Vulkan, GEngineIni);
				GConfig->Flush(true, GEngineIni);
				return;
			}
			return;
		}

	}
	return;
}

EGraphicsRHI UFriesLibraryBPLibrary::GetCurrentGraphicsRHI()
{
	// Get current platform
	FString DefaultGraphicsRHI;

	// Get current RHI by GConfig
	GConfig->GetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), DefaultGraphicsRHI, GEngineIni);

	if (DefaultGraphicsRHI == "DefaultGraphicsRHI_DX11")
	{
		return EGraphicsRHI::RHI_DX11;
	}
	return EGraphicsRHI::RHI_DX12;
}

// Ray Tracing Additional Functions

bool UFriesLibraryBPLibrary::RayTracingIsSupported()
{
	// I need to improve this later, not is very good. Just work with NVIDIA RTX GPUs
	if (UKismetStringLibrary::Contains(FWindowsPlatformMisc::GetPrimaryGPUBrand(), TEXT("RTX")))
	{
		return true;
	}
	return false;
}

bool UFriesLibraryBPLibrary::RayTracingIsEnabled()
{
	// Get "r.RayTracing" bool value
	return UKismetSystemLibrary::GetConsoleVariableBoolValue("r.RayTracing.Enable");
}

bool UFriesLibraryBPLibrary::SetRayTracing(const UObject* WorldContextObject, const bool bEnabled)
{
	// Verify if ray tracing is supported
	if (RayTracingIsSupported())
	{
		// Set r.RayTracing in true/false
		UKismetSystemLibrary::ExecuteConsoleCommand(WorldContextObject, bEnabled ? "r.RayTracing.Enable 1" : "r.RayTracing.Enable 0");
		// Force all ray tracing effects in true/false
		UKismetSystemLibrary::ExecuteConsoleCommand(WorldContextObject, bEnabled ? "r.RayTracing.ForceAllRayTracingEffects 1" :
			"r.RayTracing.ForceAllRayTracingEffects 0");
		return true;
	}
	return false;
}
