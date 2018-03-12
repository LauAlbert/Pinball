// Fill out your copyright notice in the Description page of Project Settings.

#include "Flipper.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AFlipper::AFlipper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	FlipperMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlipperMeshComp"));
	FlipperMeshComp->SetupAttachment(RootComponent);





}

// Called when the game starts or when spawned
void AFlipper::BeginPlay()
{
	Super::BeginPlay();

	if (FlipType == EFlipType::FT_Left)
	{
		FlipperMeshComp->SetRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));
		StartRotation = FRotator(0.0f, -20.0f, 0.0f);
		EndRotation = FRotator(0.0f, 20.0f, 0.0f);
	}
	else {
		StartRotation = FRotator(0.0f, 20.0f, 0.0f);
		EndRotation = FRotator(0.0f, -20.0f, 0.0f);
	}
	FlipperMeshComp->SetRelativeRotation(StartRotation);

}

void AFlipper::Flip()
{
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(FlipperMeshComp, FVector(0.0f), EndRotation, false, false, 0.02f, false, EMoveComponentAction::Type::Move, LatentInfo);

}

void AFlipper::Flop()
{
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(FlipperMeshComp, FVector(0.0f), StartRotation, false, false, 0.02f, false, EMoveComponentAction::Type::Move, LatentInfo);
}

// Called every frame
void AFlipper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
}

