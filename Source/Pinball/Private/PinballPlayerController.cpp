// Fill out your copyright notice in the Description page of Project Settings.

#include "PinballPlayerController.h"
#include "Components/InputComponent.h"
#include "EngineUtils.h"
#include "Flipper.h"

void APinballPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("RightFlipper", EInputEvent::IE_Pressed, this, &APinballPlayerController::RFlip);
	InputComponent->BindAction("RightFlipper", EInputEvent::IE_Released, this, &APinballPlayerController::RFlop);
	InputComponent->BindAction("LeftFlipper", EInputEvent::IE_Pressed, this, &APinballPlayerController::LFlip);
	InputComponent->BindAction("LeftFlipper", EInputEvent::IE_Released, this, &APinballPlayerController::LFlop);
}

void APinballPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	for (TActorIterator<AFlipper> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AFlipper *flipper = *ActorItr;
		if (flipper->GetFlipType() == EFlipType::FT_Right)
		{
			RightFlippers.Add(flipper);
		}
		else if (flipper->GetFlipType() == EFlipType::FT_Left)
		{
			LeftFlippers.Add(flipper);
		}
	}
}

void APinballPlayerController::RFlip()
{
	for (int32 i = 0; i < RightFlippers.Num(); i++)
	{
		RightFlippers[i]->Flip();
	}
}

void APinballPlayerController::RFlop()
{
	for (int32 i = 0; i < RightFlippers.Num(); i++)
	{
		RightFlippers[i]->Flop();
	}
}

void APinballPlayerController::LFlip()
{
	for (int32 i = 0; i < LeftFlippers.Num(); i++)
	{
		LeftFlippers[i]->Flip();
	}
}

void APinballPlayerController::LFlop()
{
	for (int32 i = 0; i < LeftFlippers.Num(); i++)
	{
		LeftFlippers[i]->Flop();
	}
}
