// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueComponent.h"

#include "BaseDialogueWidget.h"


// Sets default values for this component's properties
UDialogueComponent::UDialogueComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDialogueComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDialogueComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UDialogueComponent::CreateDialogueWidget()
{
	if (!DialogueWidgetClass) return;

	UBaseDialogueWidget* Widget = CreateWidget<UBaseDialogueWidget>(GetWorld()->GetFirstPlayerController(), DialogueWidgetClass);
	Widget->DialogueComp = this;
	Widget->AddToViewport();
}

void UDialogueComponent::StartDialogue()
{
	if (!DialogueImages.IsValidIndex(0))
	{
		UE_LOG(LogTemp, Warning, TEXT("UDialogueComponent: 대화 이미지가 없습니다."));
		FinishDialogue();
		return;
	}

	CurrentIndex = 0;
	OnDialogueChanged.Broadcast(DialogueImages[CurrentIndex]);
}

void UDialogueComponent::NextDialogue()
{
	if (DialogueImages.Num() == 0) return;

	CurrentIndex++;
	if (DialogueImages.IsValidIndex(CurrentIndex))
	{
		OnDialogueChanged.Broadcast(DialogueImages[CurrentIndex]);
	}
	else
	{
		FinishDialogue();
	}
}

void UDialogueComponent::FinishDialogue()
{
	OnDialogueFinished.Broadcast();
	CurrentIndex = 0;
}
