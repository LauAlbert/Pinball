// Fill out your copyright notice in the Description page of Project Settings.

#include "Ball.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	MeshComp->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MeshComp->AddImpulse(FVector(0.0f, -2000.0f, 0.0f) * DeltaTime, NAME_None, true);
	//FHitResult Hit;
	//if (GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), GetActorLocation() - FVector(0.0f, 0.0f, 500.0f), ECollisionChannel::ECC_Visibility))
	//{
	//	//UE_LOG(LogTemp, Warning, TEXT("%s"), *Hit.ImpactNormal.ToString());
	//	//MeshComp->AddImpulse(Hit.ImpactNormal * (-1.0f) * (200.0f * DeltaTime), NAME_None, true);
	//}
}

