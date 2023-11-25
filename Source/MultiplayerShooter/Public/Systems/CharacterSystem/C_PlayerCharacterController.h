// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_PlayerCharacterController.generated.h"

// Forward declarations
class AC_PlayerCharacterHUD;

UCLASS()
class MULTIPLAYERSHOOTER_API AC_PlayerCharacterController : public APlayerController
{
	GENERATED_BODY()
	
#pragma region General
// Variables
public:
	UPROPERTY(BlueprintReadOnly, Category = References, Replicated)
	AC_PlayerCharacterHUD* PlayerCharacterHUD;

	UPROPERTY(BlueprintReadOnly, Category = References, Replicated)
	class AC_PlayerCharacter* PlayerControlled;

// Functions
	virtual void BeginPlay() override;
	
	virtual void OnPossess(APawn* InPawn) override;

private:
	UFUNCTION(Server, Reliable)
	void SetNewControlledPawn_Server(APawn* InPawn);

	void SetNewControlledPawn_Server_Implementation(APawn* InPawn);

public:
	UFUNCTION(Client, Reliable)
	void SetHUD(const bool bVisible);

	void SetHUD_Implementation(const bool bVisible);

#pragma endregion General
};