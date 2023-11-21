// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/CharacterSystem/Widgets/C_HUDWidget.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Systems/CharacterSystem/C_PlayerCharacter.h"
#include "Systems/CharacterSystem/C_PlayerCharacterController.h"


void UC_HUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Get player state and player controller
	PlayerState = UGameplayStatics::GetPlayerState(this, 0);
	PlayerCharacterController = Cast<AC_PlayerCharacterController>(UGameplayStatics::GetPlayerController(this, 0));

	//? Remove widget if controller not valid
	if (!PlayerCharacterController || !PlayerState)
	{
		RemoveFromParent();
	}
}

void UC_HUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Get frames per second
	FramesPerSecond = 1 / InDeltaTime;

	//? Verify if player character controller is valid and get ping
	if (PlayerState)
	{
		PingInMs = PlayerState->GetPingInMilliseconds();
	}
	else
	{
		PingInMs = -1.0f;
	}
}

float UC_HUDWidget::GetHealthPercentage() const
{
	if (PlayerCharacterController->PlayerControlled)
	{
		// Divide health per max health to get health in percentage between 0 - 1
		float MaxHealthPercentage;
		const float HealthPercentage = PlayerCharacterController->PlayerControlled->GetHealthAndMaxHealth(MaxHealthPercentage);

		//? Return 0.0f if health percentage or max health is equal to 0
		if (HealthPercentage == 0.0f || MaxHealthPercentage == 0.0f)
		{
			return 0.0f;
		}
		return HealthPercentage / MaxHealthPercentage;
	}
	return 0.5f;
}
