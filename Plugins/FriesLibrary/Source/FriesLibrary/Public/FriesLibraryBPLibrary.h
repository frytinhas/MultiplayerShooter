// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "FriesLibraryTypes.h"
#include "FriesLibraryBPLibrary.generated.h"

/*
Welcome to Fries Library, here you can find some functions that can help in the development of your project. 
This plugin was originally designed for Unreal Engine 5.1.1, although over time I will update with new functions 
or for new versions of Unreal Engine.
*/

// Forward declarations
class UOverallScalability;

UCLASS()
class UFriesLibraryBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

// Development Functions (Ex: Print with different variables)

// Prints a string to the log, and optionally, to the screen
// If Print To Log is true, it will be visible in the Output Log window.
// And most importantly, it tells you where it's called
	static void PrintStringWithTell(const UObject* WorldContextObject, const FString InString = TEXT("Hello"), const bool bPrintToScreen = true, const bool bPrintToLog = true, const FLinearColor TextColor = FLinearColor(0.5, 0.0, 1.0), const float Duration = 2.f, const FName Key = NAME_None);

// Prints a boolean to the log, and optionally, to the screen
// If Print To Log is true, it will be visible in the Output Log window.
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category = "FriesLibrary|Development")
	static void PrintBoolean(const UObject* WorldContextObject, const bool bInBoolean = true, const float Duration = 2.f, const bool bPrintFunctionOwner = true, const bool bPrintToScreen = true, const bool bPrintToLog = true, const FLinearColor TextColor = FLinearColor(1.0, 0.0, 0.0), const FName Key = NAME_None);

// Prints a integer to the log, and optionally, to the screen
// If Print To Log is true, it will be visible in the Output Log window.
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category = "FriesLibrary|Development")
	static void PrintInteger(const UObject* WorldContextObject, const int32 IntegerValue = 0, const float Duration = 2.f, const bool bPrintFunctionOwner = true, const bool bPrintToScreen = true, const bool bPrintToLog = true, const FLinearColor TextColor = FLinearColor(0.0, 1.0, 0.5), const FName Key = NAME_None);

// Prints a float to the log, and optionally, to the screen
// If Print To Log is true, it will be visible in the Output Log window.
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category = "FriesLibrary|Development")
	static void PrintFloat(const UObject* WorldContextObject, const float FloatValue = 0.f, const float Duration = 2.f, const bool bPrintFunctionOwner = true, const bool bPrintToScreen = true, const bool bPrintToLog = true, const FLinearColor TextColor = FLinearColor(0.0, 1.0, 0.0), const FName Key = NAME_None);

// Prints a name to the log, and optionally, to the screen
// If Print To Log is true, it will be visible in the Output Log window.
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category = "FriesLibrary|Development")
	static void PrintName(const UObject* WorldContextObject, const FName InName = NAME_None, const float Duration = 2.f, const bool bPrintFunctionOwner = true, const bool bPrintToScreen = true, const bool bPrintToLog = true, const FLinearColor TextColor = FLinearColor(0.5, 0.0, 1.0), const FName Key = NAME_None);

// Prints a vector to the log, and optionally, to the screen
// If Print To Log is true, it will be visible in the Output Log window.
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category = "FriesLibrary|Development")
	static void PrintVector(const UObject* WorldContextObject, const FVector VectorValue = FVector(0.f, 0.f, 0.f), const float Duration = 2.f, const bool bPrintFunctionOwner = true, const bool bPrintToScreen = true, bool bPrintToLog = true, const FLinearColor TextColor = FLinearColor(1.0, 1.0, 0.0), const FName Key = NAME_None);

// Prints a rotator to the log, and optionally, to the screen
// If Print To Log is true, it will be visible in the Output Log window.
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category = "FriesLibrary|Development")
	static void PrintRotator(const UObject* WorldContextObject, const FRotator RotatorValue = FRotator(0.f, 0.f, 0.f), const float Duration = 2.f, const bool bPrintFunctionOwner = true, const bool bPrintToScreen = true, bool bPrintToLog = true, const FLinearColor TextColor = FLinearColor(0.25, 0.25, 1.0), const FName Key = NAME_None);

// Prints a transform to the log, and optionally, to the screen
// If Print To Log is true, it will be visible in the Output Log window.
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category = "FriesLibrary|Development")
	static void PrintTransform(const UObject* WorldContextObject, const FTransform& TransformValue, const float Duration = 2.f, const bool bPrintFunctionOwner = true, const bool bPrintToScreen = true, const bool bPrintToLog = true, const FLinearColor TextColor = FLinearColor(1.0, 0.25, 0.0), const FName Key = NAME_None);

// Prints a object to the log, and optionally, to the screen
// If Print To Log is true, it will be visible in the Output Log window.
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category = "FriesLibrary|Development")
	static void PrintObject(const UObject* WorldContextObject, const UObject* Object, const float Duration = 2.f, const bool bPrintFunctionOwner = true, const bool bPrintToScreen = true, const bool bPrintToLog = true, const bool bPrintIfInvalid = true,const FLinearColor TextColor = FLinearColor(0.0, 0.25, 1.0), const FName Key = NAME_None);

// Random Things that can help you
	// Get a random letter, is useful for generating random text, as a plate
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FriesLibrary|Math|Random")
	static FString RandomLetter(const bool bToUpper = true);

// Random Things that can help you
	// Get a random letter by range, is useful for generating random text, as a plate
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FriesLibrary|Math|Random")
	static FString RandomLetterInRange(int32 Min = 0, int32 Max = 26, const bool bToUpper = true);

// Random Things that can help you
	// Verify that the pawn (Target) is controlled by AI (Deprecated, use "IsBotControlled")
	// In the next commit this function will be removed!
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FriesLibrary|Pawn", meta = (DeprecatedFunction))
	static bool IsAIControlled(const APawn* Target);

// Additional Functions to Game User Settings
	// Get current ambient occlusion method
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "get ambient"), Category = "FriesLibrary|Settings|Ambient Occlusion")
	static EFlAmbientOcclusion GetAmbientOcclusion();

// Additional Functions to Game User Settings
	// Get current anti-aliasing method
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "get anti"), Category = "FriesLibrary|Settings|Anti-Aliasing")
	static EFlAntiAliasingMethod GetAntiAliasingMethod();

// Additional Functions to Game User Settings
	// Get current global illumination method
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "get global"), Category = "FriesLibrary|Settings|Anti-Aliasing")
	static EFlGlobalIlluminationMethod GetGlobalIllumination();
	
// Additional Functions to Game User Settings
	// Set ambient occlusion method
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "set ambient"), Category = "FriesLibrary|Settings|Ambient Occlusion")
	static void SetAmbientOcclusion(const UObject* WorldContextObject, const EFlAmbientOcclusion NewAmbientOcclusion, const bool bSaveInConfig = true);

// Additional Functions to Game User Settings
	// Set anti-aliasing method
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "set anti"), Category = "FriesLibrary|Settings|Anti-Aliasing")
	static void SetAntiAliasingMethod(const UObject* WorldContextObject, const EFlAntiAliasingMethod NewAntiAliasingMethod, const bool bSaveInConfig = true);

// Additional Functions to Game User Settings
	// Set global illumination method
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "set global"), Category = "FriesLibrary|Settings|Illumination")
	static void SetGlobalIlluminationMethod(const UObject* WorldContextObject, const EFlGlobalIlluminationMethod NewGlobalIllumination, const bool bSaveInConfig = true);
	
// Additional Functions to Game User Settings
	// Save and apply all game user settings
	UFUNCTION(BlueprintCallable, Category = "FriesLibrary|Settings")
	static void SaveGameUserSettings();

// Additional Functions to Game User Settings
	// Get scalability level by scalability type
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "scalability"), Category = "FriesLibrary|Settings|Scalability")
    static EFlEngineScalabilityLevel GetScalabilityLevel(const EFlEngineScalabilityType ScalabilityToGet);

// Additional Functions to Game User Settings
	// Modify scalability by level
	UFUNCTION(BlueprintCallable, meta = (Keywords = "scalability"), Category = "FriesLibrary|Settings|Scalability")
    static void ModifyScalability(const EFlEngineScalabilityType ScalabilityToModify, const EFlEngineScalabilityLevel NewScalabilityLevel, const bool bSaveInConfig = true);

// Additional Functions to Game User Settings
	// Modify all scalability types by level
	UFUNCTION(BlueprintCallable, meta = (Keywords = "scalability"), Category = "FriesLibrary|Settings|Scalability")
    static void SetOverallScalability(const UOverallScalability* OverallData, const EFlEngineScalabilityLevel NewScalabilityLevel);
	
/// RHI Functions
	// Set current RHI in the game (Needs restart)
	UFUNCTION(BlueprintCallable, Category = "FriesLibrary|Settings|RHI")
	static void SetGraphicsRHI(const EGraphicsRHI GraphicsRHI);
// RHI Functions
	// Get current RHI in the game (Needs restart)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FriesLibrary|Settings|RHI")
	static EGraphicsRHI GetCurrentGraphicsRHI();

// Ray Tracing Additional Functions
	// Verify if ray tracing is available in current GPU.
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "raytracing"), Category = "FriesLibrary|Settings|Ray Tracing")
	static bool RayTracingIsSupported();

// Ray Tracing Additional Functions
	// Verify is ray tracing is enabled.
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "raytracing"), Category = "FriesLibrary|Settings|Ray Tracing")
	static bool RayTracingIsEnabled();

// Ray Tracing Additional Functions
	// Set ray tracing enabled/disabled in current GPU if available.
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "raytracing"), Category = "FriesLibrary|Settings|Ray Tracing")
	static bool SetRayTracing(const UObject* WorldContextObject, const bool bEnabled);
};
