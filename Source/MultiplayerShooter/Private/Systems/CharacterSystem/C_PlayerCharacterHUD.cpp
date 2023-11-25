// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/CharacterSystem/C_PlayerCharacterHUD.h"
#include "Systems/CharacterSystem/C_PlayerCharacterController.h"
#include "Systems/CharacterSystem/Widgets/C_HUDWidget.h"

void AC_PlayerCharacterHUD::BeginPlay()
{
	Super::BeginPlay();
	
	// Set player character hud reference in player controller and set hud on
	PlayerCharacterController = Cast<AC_PlayerCharacterController>(GetNetOwningPlayer()->PlayerController);

	//? If player character controller is valid, add hud to player screen and set hud variable in player controller
	if (PlayerCharacterController && HasAuthority())
	{
		PlayerCharacterController->PlayerCharacterHUD = this;
		SetHUD(true);
	}
}

void AC_PlayerCharacterHUD::SetHUD(const bool bVisible)
{
	//? Verify if need turn on/off the hud
	if (bVisible)
	{
		//? Verify if don't exist hud to create a new
		if (!HUDWidgetReference)
		{
			//? Create widget and if valid, add to your viewport
			HUDWidgetReference = CreateWidget<UC_HUDWidget>(GetWorld(), WidgetToSpawn);
			if (HUDWidgetReference)
			{
				HUDWidgetReference->AddToViewport();
			}
		}
	}
	else
	{
		//? Verify if exist hud to destroy
		if (HUDWidgetReference)
		{
			// Remove widget from viewport and destroy reference
			HUDWidgetReference->RemoveFromParent();
			HUDWidgetReference = nullptr; 
		}
	}
}
