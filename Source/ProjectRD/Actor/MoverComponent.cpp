// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/MoverComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"


// Sets default values for this component's properties
UMoverComponent::UMoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	MoverSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MoverSoundComp"));
	MoverSoundComponent->bAutoActivate = false;
}


// Called when the game starts
void UMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OriginalLocation = GetOwner()->GetActorLocation();

	if (MoverSoundComponent && MoveSound)
	{
		MoverSoundComponent->SetSound(MoveSound);
		MoverSoundComponent->SetRelativeLocation(OriginalLocation);
	}

}


// Called every frame
void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	FVector TargetLocation = OriginalLocation;

	if (bShouldMove)
	{
		TargetLocation = OriginalLocation + MoveOffset;
	}

	FVector CurrentLocation = GetOwner()->GetActorLocation();
	float Speed = MoveOffset.Length() / MoveTime;

	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	GetOwner()->SetActorLocation(NewLocation);

	if (MoverSoundComponent && MoveSound)
	{
		if (CurrentLocation.Equals(NewLocation, 1.f))
		{
			if (MoverSoundComponent->IsPlaying())
			{
				MoverSoundComponent->Stop();
			}
		}
		else
		{
			if (!MoverSoundComponent->IsPlaying())
			{
				MoverSoundComponent->Play();
			}
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("CurrentLocation: %s"), *CurrentLocation.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("NewLocation: %s"), *NewLocation.ToString());
}

void UMoverComponent::SetShouldMove(bool bNewShouldMove)
{
	bShouldMove = bNewShouldMove;
}

