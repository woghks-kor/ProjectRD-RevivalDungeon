// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInteractableActor.h"
#include "BaseDialogueActor.generated.h"


UCLASS()
class PROJECTRD_API ABaseDialogueActor : public ABaseInteractableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseDialogueActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract() override;

	UFUNCTION()
	void OnInteractFinished();

public:
	UPROPERTY(VisibleAnywhere)
	class UDialogueComponent* DialogueComp;

};
