// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerShooter/Public/Systems/CharacterSystem/C_PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AC_PlayerCharacter::AC_PlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->bOwnerNoSee = true;
	
	// Create camera spring arm and camera component
	PlayerCameraSa = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera SA"));
	PlayerCameraSa->SetupAttachment(GetMesh(), CameraSocket);
	PlayerCameraSa->TargetArmLength = 0.f;
	PlayerCameraSa->bUsePawnControlRotation = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	PlayerCamera->SetupAttachment(PlayerCameraSa);

	// Create first person mesh, only owner see this
	Mesh_1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP Mesh"));
	Mesh_1P->SetupAttachment(PlayerCameraSa);
	Mesh_1P->bOnlyOwnerSee = true;
	Mesh_1P->CastShadow = false;
}

// Called when the game starts or when spawned
void AC_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

