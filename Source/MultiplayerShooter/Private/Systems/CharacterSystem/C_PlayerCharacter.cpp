// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerShooter/Public/Systems/CharacterSystem/C_PlayerCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetTextLibrary.h"
#include "Net/UnrealNetwork.h"
#include "MultiplayerShooter/Public/Systems/WeaponSystem/C_WeaponProjectile.h"
#include "Systems/CharacterSystem/C_PlayerCharacterController.h"
#include "Systems/CharacterSystem/C_PlayerCharacterHUD.h"

#pragma region General
// Sets default values
AC_PlayerCharacter::AC_PlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	GetMesh()->bOwnerNoSee = true;
	ProjectileActorClass = AC_WeaponProjectile::StaticClass();
	
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

	// Create weapon mesh and ammo quantity
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(Mesh_1P, "GripPoint");
	WeaponMesh->CastShadow = false;

	AmmoQuantity = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Ammo Quantity"));
	AmmoQuantity->SetupAttachment(WeaponMesh);
}

// Called when the game starts or when spawned
void AC_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set bullets in mag and update value in ammo quantity text
	BulletsInMag = MaxBulletsInMag;
	AmmoQuantity->SetText(UKismetTextLibrary::Conv_IntToText(BulletsInMag));
}

// Called every frame
/*void AC_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}*/

// Called to bind functionality to input
void AC_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AC_PlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AC_PlayerCharacter, bIsReloading)
	DOREPLIFETIME(AC_PlayerCharacter, bInFireRateDelay)
	DOREPLIFETIME(AC_PlayerCharacter, BulletsInMag)
	DOREPLIFETIME(AC_PlayerCharacter, Health)
	DOREPLIFETIME(AC_PlayerCharacter, StrafeSide)
	DOREPLIFETIME(AC_PlayerCharacter, StrafeSideRotation)
	DOREPLIFETIME(AC_PlayerCharacter, PlayerCharacterController)
}

float AC_PlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	//? Check that the player has not caused any damage to himself
	if (DamageCauser != this)
	{
		// Decrease life by damage
		Health = UKismetMathLibrary::Clamp(Health - DamageAmount, 0.f, MaxHealth);

		//? Verify if player is dead
		if (Health == 0.f)
		{
			KillPlayerServer();
		}
		return DamageAmount;
	}
	return 0.f;
}

void AC_PlayerCharacter::SetPlayerRunning_Implementation(const bool bRun)
{
	// Stop strafe to run
	StrafeCharacter(0.0f);
	// Set max walk speed bt bRun
	GetCharacterMovement()->MaxWalkSpeed = bRun ? 900.0f : 600.0f;
}

void AC_PlayerCharacter::KillPlayerServer_Implementation()
{
	// Enable physics in mesh and disable capsule collision
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->AddImpulse(GetActorForwardVector() * -10000.f);

	// Apply cosmetic things to client
	KillPlayerClient();

	// Respawn character after 5s
	GetWorldTimerManager().SetTimer(RespawnCharacterTimerHandle, [this]
	{
		RespawnPlayerServer();
	},
	5.0f, false);
}

void AC_PlayerCharacter::KillPlayerClient_Implementation()
{
	// Disable player input
	DisableInput(PlayerCharacterController);
	// Hide 1P things and disable hud
	PlayerCharacterController->SetHUD(false);
	Mesh_1P->SetHiddenInGame(true);
	WeaponMesh->SetHiddenInGame(true);
	AmmoQuantity->SetHiddenInGame(true);
}

void AC_PlayerCharacter::RespawnPlayerServer_Implementation()
{
	// Get all player starts in the map
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);

	// Spawn new player character by random player start location
	const int PlayerStartIndex = FMath::RandRange(0, PlayerStarts.Num() - 1);
	RespawnPlayerClient(GetWorld()->SpawnActor<AC_PlayerCharacter>(GetClass(), PlayerStarts[PlayerStartIndex]->GetTransform()));

	// Destroy this character
	Destroy();
}

void AC_PlayerCharacter::RespawnPlayerClient_Implementation(AC_PlayerCharacter* NewCharacter)
{
	// Possess new character
	PlayerCharacterController->Possess(NewCharacter);
	// Enable input and hud
	EnableInput(PlayerCharacterController);
	PlayerCharacterController->SetHUD(true);
}

#pragma endregion General

#pragma region Weapon System
void AC_PlayerCharacter::UpdateBulletsInMag() const
{
	// Update bullets in mag text in client
	AmmoQuantity->SetText(UKismetTextLibrary::Conv_IntToText(BulletsInMag));
}

void AC_PlayerCharacter::UpdateStrafeSide() const
{
	// Update strafe side in client
	PlayerCameraSa->SetRelativeRotation(StrafeSideRotation);

	PlayerCameraSa->SocketOffset.Y = StrafeSide == 1.0f ? 10.0f : StrafeSide == -1.0f ? -10.0f : 0.0f;
}

void AC_PlayerCharacter::WeaponFireClient_Implementation()
{
	//? Spawn fire effect if valid
	if (FireEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached(FireEffect, WeaponMesh, "Muzzle", FVector(0.0f, 0.0f, 0.0f),
			FRotator(0.0f, 0.0f, 0.0f), EAttachLocation::SnapToTarget, true);
	}

	//? Spawn sound effect if valid
	if (SoundEffect)
	{
		UGameplayStatics::SpawnSoundAttached(SoundEffect, WeaponMesh, "Muzzle", FVector(0.0f, 0.0f, 0.0f),
			FRotator(0.0f, 0.0f, 0.0f), EAttachLocation::SnapToTarget);
	}
}

void AC_PlayerCharacter::WeaponFireServer_Implementation()
{
	//? Verify if player not reloading weapon or in fire rate delay
	if (!bIsReloading && !bInFireRateDelay && Health != 0.0f && ProjectileActorClass != nullptr)
	{
		//? Verify if have bullets in mag, if not, reload weapon
		if (BulletsInMag > 0)
		{
			const FRotator ProjectileRotation = UKismetMathLibrary::FindLookAtRotation(WeaponMesh->GetSocketLocation(SpawnProjectileWeaponSocket),
				PlayerCamera->GetComponentLocation() + PlayerCamera->GetForwardVector() * 10000.f);
			const FTransform SpawnTransform = FTransform(
				ProjectileRotation,
				WeaponMesh->GetSocketLocation(SpawnProjectileWeaponSocket),
				FVector(1.f, 1.f, 1.f));
			// Spawn projectile by class (define ProjectileActorClass in blueprint, or it's C_WeaponProjectile by default)
			AC_WeaponProjectile* ProjectileRef = GetWorld()->SpawnActor<AC_WeaponProjectile>(ProjectileActorClass, SpawnTransform);
			ProjectileRef->PlayerWhoShot = this;
			
			// Decrease one bullet in mag and active fire rate delay
			BulletsInMag--;
			UpdateBulletsInMag();
			bInFireRateDelay = true;
			GetWorldTimerManager().SetTimer(ExitOfFireRateDelayTimerHandle, [this]	
			{
				bInFireRateDelay = false;
			},
			WeaponFireRate, false);
			// Spawn weapon fire effects in client
			WeaponFireClient();
			return;
		}
		ReloadWeapon();
	}
}

void AC_PlayerCharacter::StrafeCharacter_Implementation(const float TargetStrafeSide)
{
	//? Verify if player is not running to strafe character
	if (GetCharacterMovement()->MaxWalkSpeed <= 600.0f)
	{
		// Create target rotation and did a verifications
		StrafeSide = TargetStrafeSide;
		FRotator TargetRotation = PlayerCameraSa->GetRelativeRotation();

		//? Verify if strafe side is equal a 1.0f or -1.0f and apply roll rotation
		if (TargetStrafeSide == 1.0f)
		{
			TargetRotation.Roll = 15.0f;
			PlayerCameraSa->SetRelativeRotation(TargetRotation);
			PlayerCameraSa->SocketOffset.Y = 10.0f;
			StrafeSideRotation = TargetRotation;
			return;
		}
		else if (TargetStrafeSide == -1.0f)
		{
			TargetRotation.Roll = -15.0f;
			PlayerCameraSa->SetRelativeRotation(TargetRotation);
			PlayerCameraSa->SocketOffset.Y = -10.0f;
			StrafeSideRotation = TargetRotation;
			return;
		}

		// Set roll rotation in 0.0f
		TargetRotation.Roll = 0.0f;
		PlayerCameraSa->SetRelativeRotation(TargetRotation);
		PlayerCameraSa->SocketOffset.Y = 0.0f;
		StrafeSideRotation = TargetRotation;
	}
}

void AC_PlayerCharacter::ReloadWeapon_Implementation()
{
	//? Verify if need reload
	if (!bIsReloading &&  BulletsInMag != MaxBulletsInMag)
	{
		// Set bIsReloading to true, for player don't fire
		bIsReloading = true;
		// Set timer to reload weapon
		GetWorldTimerManager().SetTimer(EndReloadWeaponTimerHandle, [this]
		{
			BulletsInMag = MaxBulletsInMag;
			UpdateBulletsInMag();
			bIsReloading = false;
		},
		ReloadTime, false);
	}
}
#pragma endregion Weapon System
