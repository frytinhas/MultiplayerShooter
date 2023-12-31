// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/WeaponSystem/C_WeaponProjectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Systems/CharacterSystem/C_PlayerCharacter.h"

// Sets default values
AC_WeaponProjectile::AC_WeaponProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the main components of a projectile
	ProjectileCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Projectile Collision"));
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->SetupAttachment(ProjectileCollision);
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileComponent->OnProjectileBounce.AddDynamic(this, &AC_WeaponProjectile::OnProjectileBounce);
	ProjectileComponent->OnProjectileStop.AddDynamic(this, &AC_WeaponProjectile::OnProjectileStop);
}

// Called when the game starts or when spawned
void AC_WeaponProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_WeaponProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_WeaponProjectile::OnProjectileBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	//? If is a player, apply damage to player than was hit
	if (Cast<AC_PlayerCharacter>(ImpactResult.GetActor()))
	{
		UGameplayStatics::ApplyDamage(ImpactResult.GetActor(), ProjectileDamage, nullptr, PlayerWhoShot, UDamageType::StaticClass());
		// Warn the player who fired that the projectile hit another player
		PlayerWhoShot->OnHitPlayerWithBullet.Broadcast();
	}
}

void AC_WeaponProjectile::OnProjectileStop(const FHitResult& ImpactResult)
{
	if (ProjectileComponent->bShouldBounce)
	{
		// Only destroy projectile
		Destroy();
	}
	else
	{
		//? If is a player, apply damage to player than was hit and destroy projectile after verification
		if (AC_PlayerCharacter* PlayerWhoHit; Cast<AC_PlayerCharacter>(ImpactResult.GetActor()))
		{
			PlayerWhoHit = Cast<AC_PlayerCharacter>(ImpactResult.GetActor());
			UGameplayStatics::ApplyDamage(PlayerWhoHit, ProjectileDamage, nullptr, PlayerWhoShot, UDamageType::StaticClass());
			//? Warn the player (if valid) who fired that the projectile hit another player
			if (float MaxHealth; PlayerWhoShot && PlayerWhoHit->GetHealthAndMaxHealth(MaxHealth) != 0.0f)
			{
				PlayerWhoShot->OnHitPlayerWithBullet.Broadcast();
			}
		}
		Destroy();
	}
	
}

