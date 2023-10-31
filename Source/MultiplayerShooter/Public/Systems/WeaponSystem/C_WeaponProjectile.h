// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_WeaponProjectile.generated.h"

UCLASS()
class MULTIPLAYERSHOOTER_API AC_WeaponProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_WeaponProjectile();

// Components
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<class UProjectileMovementComponent> ProjectileComponent;

// Variables
	UPROPERTY(EditDefaultsOnly, Category = Info)
	float ProjectileDamage = 10.f;
	
// Functions
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnProjectileBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);
	
	UFUNCTION()
	void OnProjectileStop(const FHitResult& ImpactResult);
};
