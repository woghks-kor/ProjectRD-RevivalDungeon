// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/TriggerBoxComponent.h"

#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"
#include "Actor/MoverComponent.h"
#include "Kismet/GameplayStatics.h"


UTriggerBoxComponent::UTriggerBoxComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
    StandSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("StandSoundComp"));
    StandSoundComponent->bAutoActivate = false;
}

void UTriggerBoxComponent::BeginPlay()
{
    Super::BeginPlay();

    // ...
    if (MoveActor)
    {
        UMoverComponent* NewMover = MoveActor->GetComponentByClass<UMoverComponent>();
        if (NewMover) 
        {
            SetMover(NewMover); 
        }
    }

    if (StandSoundComponent && StandSound)
    {
        StandSoundComponent->SetSound(StandSound);
    }
}

void UTriggerBoxComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
    AActor* Actor = GetAcceptableActor();
    if (Actor != nullptr)
    {
        if (!bIsStand)
        {
            if (StandSoundComponent && StandSound)
            {
                //UGameplayStatics::PlaySoundAtLocation(GetWorld(), StandSound, GetComponentLocation());
                StandSoundComponent->Play();
            }

            bIsStand = true;
        }

        UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
        if (Component != nullptr)
        {
            Component->SetSimulatePhysics(false);
        }

        FBoxSphereBounds TriggerBoxBounds = CalcBounds(GetComponentTransform());
        float TriggerFloorZ = TriggerBoxBounds.Origin.Z - TriggerBoxBounds.BoxExtent.Z;

        FVector TriggerLocation = GetComponentLocation();

        FVector NewActorLocation = FVector(TriggerLocation.X, TriggerLocation.Y, TriggerFloorZ);
        Actor->SetActorLocation(NewActorLocation, false, nullptr, ETeleportType::TeleportPhysics);
        FRotator NewRotation = GetRelativeRotation();
        Actor->SetActorRelativeRotation(NewRotation);

        if (Mover != nullptr)
        {
            Mover->SetShouldMove(true);
        }
    }
    else
    {
        bIsStand = false;
        if (StandSoundComponent && StandSound)
        {
            StandSoundComponent->Stop();
        }

        if (Mover != nullptr)
        {
            Mover->SetShouldMove(false);
        }
    }
}

void UTriggerBoxComponent::SetMover(UMoverComponent* NewMover)
{
    Mover = NewMover;
}

bool UTriggerBoxComponent::IsActorInTrigger() const
{
    AActor* Actor = GetAcceptableActor();
    if (Actor) return true;

    return false;
}

AActor* UTriggerBoxComponent::GetAcceptableActor() const
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);

    for (AActor* Actor : Actors)
    {
        bool HasAcceptableTag = Actor->ActorHasTag(TargetActorTag);
        bool IsGrabbed = Actor->ActorHasTag("Grabbed");
        //UE_LOG(LogTemp, Warning, TEXT("HasAcceptableTag: %hs"), HasAcceptableTag ? "True" : "False");
        //UE_LOG(LogTemp, Warning, TEXT("IsGrabbed: %hs"), IsGrabbed ? "True" : "False");
        if (HasAcceptableTag && !IsGrabbed)
        {
            return Actor;
        }
    }

    return nullptr;
}
