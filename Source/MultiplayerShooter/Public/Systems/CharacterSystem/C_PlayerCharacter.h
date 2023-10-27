// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_PlayerCharacter.generated.h"

// Forward declarations
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class MULTIPLAYERSHOOTER_API AC_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_PlayerCharacter();

// Components
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> PlayerCameraSa;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> Mesh_1P;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<UCameraComponent> PlayerCamera;

// Variables
	UPROPERTY(EditDefaultsOnly, Category = Info)
	FName CameraSocket = "head";

// Functions
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
