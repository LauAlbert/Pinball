// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bumpers.generated.h"

class UCapsuleComponent;
class UTimelineComponent;
class UCurveFloat;
class UPointLightComponent;

UCLASS()
class PINBALL_API ABumpers : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABumpers();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BumperMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BumperMechanism;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPointLightComponent* PointLightComp;

	UPROPERTY()
	UTimelineComponent* MyTimeline;

	UPROPERTY(EditDefaultsOnly, Category = "Light")
	UCurveFloat* FloatCurve;

	UFUNCTION()
	void TimelineCallback(float val);

	UFUNCTION()
	void TimelineFinishedCallback();

	void PlayTimeline();




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
