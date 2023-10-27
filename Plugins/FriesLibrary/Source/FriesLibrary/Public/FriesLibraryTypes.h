#pragma once

#include "FriesLibraryTypes.generated.h"

// Enumeration
// Enumeration used to get/set current RHI mode
UENUM(BlueprintType, Category = "FriesLibrary|Data|Enums")
enum class EGraphicsRHI : uint8
{
	RHI_DX11    UMETA(DisplayName = "DirectX 11"),
	RHI_DX12    UMETA(DisplayName = "DirectX 12"),
	RHI_Vulkan  UMETA(DisplayName = "Vulkan")
};

// Enumeration used to get/set current ambient occlusion method
UENUM(BlueprintType, Category = "FriesLibrary|Data|Enums")
enum class EFlAmbientOcclusion : uint8
{
	SSAO UMETA(DisplayName = "SSAO"),
	GTAO UMETA(DisplayName = "GTAO")
};

// Enumeration used to get/set current Anti-aliasing method
UENUM(BlueprintType, Category = "FriesLibrary|Data|Enums")
enum class EFlAntiAliasingMethod : uint8
{
	None UMETA(DisplayName = "None"),
	FXAA UMETA(DisplayName = "FXAA"),
	TAA  UMETA(DisplayName = "TAA"),
	MSAA UMETA(DisplayName = "MSAA"),
	TSR  UMETA(DisplayName = "TSR")
};

// Enumeration used to get/set current global illumination method
UENUM(BlueprintType, Category = "FriesLibrary|Data|Enums")
enum class EFlGlobalIlluminationMethod : uint8
{
	None       UMETA(DisplayName = "None"),
	Lumen    UMETA(DisplayName = "Lumen"),
	SSGI      UMETA(DisplayName = "SSGI"),
	RTGI     UMETA(DisplayName = "RTGI"),
	Plugin UMETA(DisplayName = "Plugin")
};

// Create EEngineScalabilityType
UENUM(BlueprintType, Category = "FriesLibrary|Data|Enums")
enum class EFlEngineScalabilityType : uint8
{
	Overall             UMETA(DisplayName = "Overall"),
	ViewDistance        UMETA(DisplayName = "ViewDistance"),
	AntiAliasing        UMETA(DisplayName = "AntiAliasing"),
	PostProcessing      UMETA(DisplayName = "PostProcessing"),
	Shadows             UMETA(DisplayName = "Shadows"),
	GlobalIllumination  UMETA(DisplayName = "GlobalIllumination"),
	Reflections         UMETA(DisplayName = "Reflections"),
	Textures            UMETA(DisplayName = "Textures"),
	Effects             UMETA(DisplayName = "Effects"),
	Foliage             UMETA(DisplayName = "Foliage"),
	Shading             UMETA(DisplayName = "Shading")
};

// Create EEngineScalabilityLevel
UENUM(BlueprintType, Category = "FriesLibrary|Data|Enums")
enum class EFlEngineScalabilityLevel : uint8
{
	Low       UMETA(DisplayName = "Low"),
	Medium    UMETA(DisplayName = "Medium"),
	High      UMETA(DisplayName = "High"),
	Ultra     UMETA(DisplayName = "Ultra"),
	Cinematic UMETA(DisplayName = "Cinematic")
};

// Structures
// Create structure used by OverallScalability
USTRUCT(BlueprintType, Category = "FriesLibrary|Data|Structs")
struct FAllScalabilitys
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FriesLibrary|Data|Structs")
	EFlEngineScalabilityLevel ViewDistance = EFlEngineScalabilityLevel::Low;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FriesLibrary|Data|Structs")
	EFlEngineScalabilityLevel AntiAliasing = EFlEngineScalabilityLevel::Low;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FriesLibrary|Data|Structs")
	EFlEngineScalabilityLevel PostProcessing = EFlEngineScalabilityLevel::Low;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FriesLibrary|Data|Structs")
	EFlEngineScalabilityLevel Shadows = EFlEngineScalabilityLevel::Low;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FriesLibrary|Data|Structs")
	EFlEngineScalabilityLevel GlobalIllumination = EFlEngineScalabilityLevel::Low;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FriesLibrary|Data|Structs")
	EFlEngineScalabilityLevel Reflections = EFlEngineScalabilityLevel::Low;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FriesLibrary|Data|Structs")
	EFlEngineScalabilityLevel Textures = EFlEngineScalabilityLevel::Low;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FriesLibrary|Data|Structs")
	EFlEngineScalabilityLevel Effects = EFlEngineScalabilityLevel::Low;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FriesLibrary|Data|Structs")
	EFlEngineScalabilityLevel Foliage = EFlEngineScalabilityLevel::Low;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FriesLibrary|Data|Structs")
	EFlEngineScalabilityLevel Shading = EFlEngineScalabilityLevel::Low;
};