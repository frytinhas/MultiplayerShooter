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
	UPROPERTY(BlueprintReadOnly, Category = References, Replicated)
	class AC_PlayerCharacterController* PlayerCharacterController;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Info)
	FName CameraSocket = "head";
	
	UPROPERTY(EditDefaultsOnly, Category = Info, Replicated)
	float Health = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = Info)
	float MaxHealth = 100.f;

// Functions
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	// virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Info)
	float GetHealthAndMaxHealth(float& PlayerMaxHealth) const
	{
		PlayerMaxHealth = MaxHealth;
		return Health;
	}

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	UFUNCTION(BlueprintCallable, Server, Unreliable)
	void SetPlayerRunning(const bool bRun);

	void SetPlayerRunning_Implementation(const bool bRun);
	
	UFUNCTION(Server, Reliable)
	void KillPlayerServer();

	void KillPlayerServer_Implementation();

	UFUNCTION(Client, Reliable)
	void KillPlayerClient();

	void KillPlayerClient_Implementation();

	FTimerHandle RespawnCharacterTimerHandle;
	UFUNCTION(Server, Reliable)
	void RespawnPlayerServer();

	void RespawnPlayerServer_Implementation();

	UFUNCTION(Server, Reliable)
	void RespawnPlayerClient(AC_PlayerCharacter* NewCharacter);

	void RespawnPlayerClient_Implementation(AC_PlayerCharacter* NewCharacter);
	
#pragma endregion General
	
#pragma region Weapon System
// Components
protected:
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

	UPROPERTY(EditDefaultsOnly, Category = "Weapon System")
	class UNiagaraSystem* FireEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon System")
	USoundBase* SoundEffect;

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
	float ReloadTime = 1.9f;
	
	UPROPERTY(Category = "Weapon System", BlueprintReadOnly, Replicated)
	float StrafeSide;

	UPROPERTY(ReplicatedUsing = UpdateStrafeSide)
	FRotator StrafeSideRotation;

private:
// Timer handles
	FTimerHandle ExitOfFireRateDelayTimerHandle;
	FTimerHandle EndReloadWeaponTimerHandle;
	
// Functions
	UFUNCTION()
	void UpdateBulletsInMag() const;

	UFUNCTION()
	void UpdateStrafeSide() const;

protected:
	UFUNCTION(BlueprintCallable, Category = "Weapon System", Server, Reliable)
	void WeaponFireServer();

	void WeaponFireServer_Implementation();

	UFUNCTION(Client, Unreliable)
	void WeaponFireClient();

	void WeaponFireClient_Implementation();

	// Strafe with weapon and character (-1.0 to left, 0.0 to default, 1.0 to right)
	UFUNCTION(BlueprintCallable, Category = "Weapon System", Server, Unreliable)
	void StrafeCharacter(const float TargetStrafeSide);

	void StrafeCharacter_Implementation(const float TargetStrafeSide);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon System", Server, Reliable)
	void ReloadWeapon();
	
	void ReloadWeapon_Implementation();
		
#pragma endregion Weapon System

};
