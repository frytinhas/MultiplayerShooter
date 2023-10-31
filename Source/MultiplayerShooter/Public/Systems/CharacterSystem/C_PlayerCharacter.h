// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_PlayerCharacter.generated.h"

UCLASS()
class MULTIPLAYERSHOOTER_API AC_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_PlayerCharacter();

#pragma region General
// Components
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<class USpringArmComponent> PlayerCameraSa;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<class UCameraComponent> PlayerCamera;

// Variables
	UPROPERTY(EditDefaultsOnly, Category = Info)
	FName CameraSocket = "head";

// Functions
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	// virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
#pragma endregion General
	
#pragma region Weapon System
// Components
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> Mesh_1P;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<class UTextRenderComponent> AmmoQuantity;
	
// Variables
	UPROPERTY(EditDefaultsOnly, Category = "Weapon System")
	TSubclassOf<class AC_WeaponProjectile> ProjectileActorClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon System")
	FName SpawnProjectileWeaponSocket = "Muzzle";

	UPROPERTY(Replicated)
	bool bIsReloading = false;

	UPROPERTY(Replicated)
	bool bInFireRateDelay = false;
	
	UPROPERTY(BlueprintReadOnly, Category = "Weapon System", ReplicatedUsing = UpdateBulletsInMag)
	int BulletsInMag = 30;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon System", EditDefaultsOnly)
	int MaxBulletsInMag = 30;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon System")
	float WeaponFireRate = 0.1f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon System")
	float ReloadTime = 1.4f;

// Timer handles
	FTimerHandle ExitOfFireRateDelayTimerHandle;
	FTimerHandle EndReloadWeaponTimerHandle;
	
// Functions
	UFUNCTION()
	void UpdateBulletsInMag() const;
	
	UFUNCTION(BlueprintCallable, Category = "Weapon System", Server, Reliable)
	void WeaponFire();

	void WeaponFire_Implementation();
	
	UFUNCTION(BlueprintCallable, Category = "Weapon System", Server, Unreliable)
	void ReloadWeapon();
	
	void ReloadWeapon_Implementation();
		
#pragma endregion Weapon System

};
