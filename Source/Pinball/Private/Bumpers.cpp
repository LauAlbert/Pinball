// Fill out your copyright notice in the Description page of Project Settings.

#include "Bumpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/PointLightComponent.h"
#include "Curves/CurveFloat.h"
#include "UObject/ConstructorHelpers.h"
#include "Ball.h"

// Sets default values
ABumpers::ABumpers()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BumperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BumperMesh"));
	RootComponent = BumperMesh;

	BumperMechanism = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BumperMechanism"));
	BumperMechanism->SetupAttachment(RootComponent);

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	CapsuleComp->SetupAttachment(RootComponent);
	CapsuleComp->SetCapsuleHalfHeight(250.0f);
	CapsuleComp->SetCapsuleRadius(120.0f);

	CapsuleComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CapsuleComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);

	PointLightComp = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComp"));
	PointLightComp->SetupAttachment(RootComponent);
	PointLightComp->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	PointLightComp->SetCastShadows(false);
	PointLightComp->SetIntensity(0.0f);


}

// Called when the game starts or when spawned
void ABumpers::BeginPlay()
{
	FOnTimelineFloat onTimelineCallback;
	FOnTimelineEventStatic onTimelineFinishedCallback;

	Super::BeginPlay();

	if (FloatCurve)
	{

		MyTimeline = NewObject<UTimelineComponent>(this, FName("TimelineAnimation"));
		MyTimeline->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		this->BlueprintCreatedComponents.Add(MyTimeline);
		MyTimeline->SetNetAddressable();

		MyTimeline->SetLooping(false);
		MyTimeline->SetTimelineLength(5.0f);
		MyTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

		MyTimeline->SetPlaybackPosition(0.0f, false);

		onTimelineCallback.BindUFunction(this, FName("TimelineCallback"));
		onTimelineFinishedCallback.BindUFunction(this, FName("TimelineFinishedCallback"));
		MyTimeline->AddInterpFloat(FloatCurve, onTimelineCallback, FName("Alpha"));
		MyTimeline->SetTimelineFinishedFunc(onTimelineFinishedCallback);

		MyTimeline->RegisterComponent();
	}
	
}

void ABumpers::TimelineCallback(float val)
{
	if (BumperMechanism)
	{
		FVector NewLocation = FMath::Lerp(FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, -70.0f), val);
		BumperMechanism->SetRelativeLocation(NewLocation);
	}
	if (PointLightComp)
	{
		float NewLightIntensity = FMath::Lerp(0.0f, 5000.0f, val);
		PointLightComp->SetIntensity(NewLightIntensity);
	}
	

}

void ABumpers::TimelineFinishedCallback()
{
	UE_LOG(LogTemp, Warning, TEXT("Done"));
}

void ABumpers::PlayTimeline()
{
	if (MyTimeline != NULL)
	{
		MyTimeline->PlayFromStart();
	}
}

// Called every frame
void ABumpers::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MyTimeline != NULL)
	{
		MyTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}


	TArray<AActor*> OverlappingComps;

	CapsuleComp->GetOverlappingActors(OverlappingComps);


	for (int32 i = 0; i < OverlappingComps.Num(); i++)
	{
		//UE_LOG(LogTemp, Warning, TEXT("hi"));

		ABall* Ball = Cast<ABall>(OverlappingComps[i]);
		if (Ball)
		{
			FVector DirectionOfImpact = (GetActorLocation() - Ball->GetActorLocation()).GetSafeNormal();

			Ball->GetMeshComp()->AddImpulse(DirectionOfImpact * -2500.0f, NAME_None, true);

			PlayTimeline();
		}
	}

}

