// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SprintComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTRD_API USprintComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USprintComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void StartSprint();

	UFUNCTION(BlueprintCallable)
	void StopSprint();

	UPROPERTY(EditAnywhere)
	bool bCanSprint = true;

	UPROPERTY(EditAnywhere)
	float WalkSpeed = 250.f;

	UPROPERTY(EditAnywhere)
	float SprintSpeed = 500.f;

private:
	class ACharacter* OwnerRef;

	class UCharacterMovementComponent* MovementComp;

	bool bIsSprinting = false;
	
};
