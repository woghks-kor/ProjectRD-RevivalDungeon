// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDialogueWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "DialogueComponent.h"


void UBaseDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Button_Next) return;
	Button_Next->OnClicked.AddDynamic(this, &UBaseDialogueWidget::OnNextButtonClicked);

	if (!Button_Exit) return;
	Button_Exit->OnClicked.AddDynamic(this, &UBaseDialogueWidget::OnExitButtonClicked);

	if (!DialogueComp) return;
	DialogueComp->OnDialogueChanged.AddDynamic(this, &UBaseDialogueWidget::OnDialogueChanged);
	DialogueComp->OnDialogueFinished.AddDynamic(this, &UBaseDialogueWidget::OnDialogueFinished);
	DialogueComp->StartDialogue();

	SetInputModeUIOnly();
}

void UBaseDialogueWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (DialogueComp)
	{
		DialogueComp->OnDialogueChanged.RemoveDynamic(this, &UBaseDialogueWidget::OnDialogueChanged);
		DialogueComp->OnDialogueFinished.RemoveDynamic(this, &UBaseDialogueWidget::OnDialogueFinished);
	}
}

void UBaseDialogueWidget::OnDialogueChanged(UTexture2D* NewDialogueTexture)
{
	if (!NewDialogueTexture) return;
	DialogueImage->SetBrushFromTexture(NewDialogueTexture);
}

void UBaseDialogueWidget::OnDialogueFinished()
{
	SetInputModeGameOnly();

	RemoveFromParent();
}

void UBaseDialogueWidget::SetInputModeUIOnly()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputModeData);

	PlayerController->FlushPressedKeys();

	PlayerController->bShowMouseCursor = true;
	PlayerController->SetIgnoreLookInput(true);
}

void UBaseDialogueWidget::SetInputModeGameOnly()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = false;
	PlayerController->SetIgnoreLookInput(false);
}

void UBaseDialogueWidget::OnNextButtonClicked()
{
	if (!DialogueComp) return;
	DialogueComp->NextDialogue();
}

void UBaseDialogueWidget::OnExitButtonClicked()
{
	if (!DialogueComp) return;
	DialogueComp->FinishDialogue();
}