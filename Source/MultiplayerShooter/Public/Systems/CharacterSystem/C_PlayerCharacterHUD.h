// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "C_PlayerCharacterHUD.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSHOOTER_API AC_PlayerCharacterHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	// Function created only to manage hud by C++
	UFUNCTION(BlueprintImplementableEvent, Category = HUD)
	void SetHUD(const bool bVisible);

	void SetHUD_Implementation(const bool bVisible);
};
