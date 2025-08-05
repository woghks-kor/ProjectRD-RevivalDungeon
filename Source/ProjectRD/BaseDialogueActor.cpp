// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDialogueActor.h"

#include "DialogueComponent.h"


// Sets default values
ABaseDialogueActor::ABaseDialogueActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DialogueComp = CreateDefaultSubobject<UDialogueComponent>(TEXT("DialogueComponent"));
}

// Called when the game starts or when spawned
void ABaseDialogueActor::BeginPlay()
{
	Super::BeginPlay();
	
	DialogueComp->OnDialogueFinished.AddDynamic(this, &ABaseDialogueActor::OnInteractFinished);
}

// Called every frame
void ABaseDialogueActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseDialogueActor::OnInteract()
{
	Super::OnInteract();

	if (!bCanInteract) return;
	if (!bCanPress) return;

	DialogueComp->CreateDialogueWidget();
	bCanPress = false;
	CheckRepeat();
}

void ABaseDialogueActor::OnInteractFinished()
{
	//UE_LOG(LogTemp, Warning, TEXT("Interact Finished !"));
	bCanPress = true;
}

