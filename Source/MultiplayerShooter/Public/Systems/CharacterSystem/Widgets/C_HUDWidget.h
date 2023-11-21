// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSHOOTER_API UC_HUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
// Variables
public:
	UPROPERTY(BlueprintReadOnly, Category = References)
	class AC_PlayerCharacterController* PlayerCharacterController;

	UPROPERTY(BlueprintReadOnly, Category = References)
	APlayerState* PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = Info)
	int FramesPerSecond;

	UPROPERTY(BlueprintReadOnly, Category = Info)
	int PingInMs;
	
// Functions
protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Info)
	float GetHealthPercentage() const;
};
