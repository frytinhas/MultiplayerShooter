// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/CharacterSystem/C_PlayerCharacterAnimInstance.h"
#include "Net/UnrealNetwork.h"
#include "Systems/CharacterSystem/C_PlayerCharacter.h"

void UC_PlayerCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// Get player ref
	PlayerRef = Cast<AC_PlayerCharacter>(TryGetPawnOwner());
}

void UC_PlayerCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//? Just exec update anim if player ref is valid
	if (PlayerRef)
	{
		VerifyIfIsWalking();
	}
}

void UC_PlayerCharacterAnimInstance::VerifyIfIsWalking_Implementation()
{
	bIsWalking = PlayerRef->GetVelocity() != FVector(0.f, 0.f, 0.f);
}

