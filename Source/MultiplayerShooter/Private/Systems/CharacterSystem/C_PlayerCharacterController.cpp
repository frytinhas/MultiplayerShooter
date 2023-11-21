// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerShooter/Public/Systems/CharacterSystem/C_PlayerCharacterController.h"
#include "Net/UnrealNetwork.h"
#include "Systems/CharacterSystem/C_PlayerCharacter.h"
#include "Systems/CharacterSystem/C_PlayerCharacterHUD.h"

#pragma region General
void AC_PlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();
}

void AC_PlayerCharacterController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AC_PlayerCharacterController, PlayerCharacterHUD)
	DOREPLIFETIME(AC_PlayerCharacterController, PlayerControlled)
}

void AC_PlayerCharacterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Set new reference to player controller in character by server
	SetNewControlledPawn_Server(InPawn);
}

void AC_PlayerCharacterController::SetNewControlledPawn_Server_Implementation(APawn* InPawn)
{
	// Set new reference to player controller in character
	PlayerControlled = Cast<AC_PlayerCharacter>(InPawn);
	PlayerControlled->PlayerCharacterController = this;
}

void AC_PlayerCharacterController::SetHUD_Implementation(const bool bVisible)
{
	//? Verify if hud is valid, and set hud
	if (PlayerCharacterHUD)
	{
		PlayerCharacterHUD->SetHUD(bVisible);
	}
}
#pragma endregion General
