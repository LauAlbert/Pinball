// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Flipper.generated.h"

UENUM(BlueprintType)
enum class EFlipType: uint8
{
	FT_Right	UMETA(DisplayName="Right"),
	FT_Left		UMETA(DisplayName="Left")
};

UCLASS()
class PINBALL_API AFlipper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlipper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* FlipperMeshComp;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Properties")
	EFlipType FlipType;



private:
	FRotator StartRotation;
	FRotator EndRotation;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Flip();

	void Flop();
	
	FORCEINLINE EFlipType GetFlipType() { return FlipType; }
	
};
