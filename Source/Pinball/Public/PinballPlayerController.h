// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PinballPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PINBALL_API APinballPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override;
	
	virtual void BeginPlay() override;

	TArray<class AFlipper*> LeftFlippers;

	TArray<class AFlipper*> RightFlippers;

	void RFlip();

	void RFlop();

	void LFlip();

	void LFlop();
};
