// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/HUD.h"
#include "C_PlayerCharacterHUD.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSHOOTER_API AC_PlayerCharacterHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = References)
	class AC_PlayerCharacterController* PlayerCharacterController;
	
	UPROPERTY(EditDefaultsOnly, Category = Info)
	TSubclassOf<UUserWidget> WidgetToSpawn = UUserWidget::StaticClass();;

	UPROPERTY(BlueprintReadOnly, Category = References)
	class UC_HUDWidget* HUDWidgetReference = nullptr;
	
public:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = HUD)
	void SetHUD(const bool bVisible);
};
