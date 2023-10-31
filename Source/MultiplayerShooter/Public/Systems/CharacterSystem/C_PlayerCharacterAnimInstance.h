// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "C_PlayerCharacterAnimInstance.generated.h"

// Forward declarations
class AC_PlayerCharacter;

UCLASS()
class MULTIPLAYERSHOOTER_API UC_PlayerCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

// Variables
protected:
	UPROPERTY(BlueprintReadOnly, Category = References)
	AC_PlayerCharacter* PlayerRef;

	UPROPERTY(BlueprintReadOnly, Category = Info)
	bool bIsWalking;
	
// Functions
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION(Server, Unreliable)
	void VerifyIfIsWalking();
	
	void VerifyIfIsWalking_Implementation();
};
