// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FriesLibraryTypes.h"
#include "OverallScalability.generated.h"

UCLASS()
class FRIESLIBRARY_API UOverallScalability : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Data")
	FAllScalabilitys ScalabilityInfo;
};
