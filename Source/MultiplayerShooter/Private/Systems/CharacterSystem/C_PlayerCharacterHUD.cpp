// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/CharacterSystem/C_PlayerCharacterHUD.h"
#include "Blueprint/UserWidget.h"

void AC_PlayerCharacterHUD::BeginPlay()
{
	Super::BeginPlay();

	// Spawn hud on start
	SetHUD(true);
}

void AC_PlayerCharacterHUD::SetHUD_Implementation(const bool bVisible)
{
	GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::White, "Add set hud event in blueprint");
}
