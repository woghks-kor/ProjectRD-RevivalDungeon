// Fill out your copyright notice in the Description page of Project Settings.


#include "SprintComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values for this component's properties
USprintComponent::USprintComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void USprintComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OwnerRef = GetOwner<ACharacter>();
	MovementComp = OwnerRef->GetCharacterMovement();
	if (!MovementComp) return;
}

void USprintComponent::StartSprint()
{
	if (!bCanSprint || bIsSprinting) return;

	bIsSprinting = true;
	MovementComp->MaxWalkSpeed = SprintSpeed;
}

void USprintComponent::StopSprint()
{
	if (!bCanSprint) return;

	bIsSprinting = false;
	MovementComp->MaxWalkSpeed = WalkSpeed;
}
