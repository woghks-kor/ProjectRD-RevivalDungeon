// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleSwitchWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void UPuzzleSwitchWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Button_Exit) return;
	Button_Exit->OnClicked.AddDynamic(this, &UPuzzleSwitchWidget::OnExitButtonClicked);

	if (!Button_Red) return;
	Button_Red->OnClicked.AddDynamic(this, &UPuzzleSwitchWidget::OnRedButtonClicked);

	if (!Button_Blue) return;
	Button_Blue->OnClicked.AddDynamic(this, &UPuzzleSwitchWidget::OnBlueButtonClicked);

	if (!Button_Green) return;
	Button_Green->OnClicked.AddDynamic(this, &UPuzzleSwitchWidget::OnGreenButtonClicked);

	if (!Button_Yellow) return;
	Button_Yellow->OnClicked.AddDynamic(this, &UPuzzleSwitchWidget::OnYellowButtonClicked);

	if (CountImages[0]) { Image_Count->SetBrushFromTexture(CountImages[0]); }

	// Initialize
	if (!Answer) return;
	Count = 0;
	SetInputModeUIOnly();
}

void UPuzzleSwitchWidget::CheckPuzzleAnswer(EBUTTONCOLOR Color)
{
	// Count 확인

	if (Answer[Count] != Color)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wrong Answer"));
		if (WrongSound) { UGameplayStatics::PlaySound2D(this, WrongSound); }
		ResetPuzzle();
		return;
	}

	Count++;
	if (ClickSound) { UGameplayStatics::PlaySound2D(this, ClickSound); }
	Image_Count->SetBrushFromTexture(CountImages[Count]);

	// 퍼즐 성공일 경우
	if (Count == 4)
	{
		if (AnswerSound) { UGameplayStatics::PlaySound2D(this, AnswerSound); }
		OnPuzzleSuccess.Broadcast();
		
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		TimerManager.ClearTimer(TimerHandle);
		TimerManager.SetTimer(TimerHandle, this, &UPuzzleSwitchWidget::ClearWidget, 0.5f);
	}
}

void UPuzzleSwitchWidget::ResetPuzzle()
{
	Count = 0;
	if (CountImages[0])
	{
		Image_Count->SetBrushFromTexture(CountImages[0]);
	}

	Button_Red->SetIsEnabled(true);
	Button_Blue->SetIsEnabled(true);
	Button_Green->SetIsEnabled(true);
	Button_Yellow->SetIsEnabled(true);

}

void UPuzzleSwitchWidget::ClearWidget()
{
	RemoveFromParent();
	SetInputModeGameOnly();
}

void UPuzzleSwitchWidget::SetInputModeUIOnly()
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

void UPuzzleSwitchWidget::SetInputModeGameOnly()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = false;
	PlayerController->SetIgnoreLookInput(false);
}

void UPuzzleSwitchWidget::OnRedButtonClicked()
{
	Button_Red->SetIsEnabled(false);
	CheckPuzzleAnswer(EBUTTONCOLOR::RED);
}

void UPuzzleSwitchWidget::OnBlueButtonClicked()
{
	Button_Blue->SetIsEnabled(false);
	CheckPuzzleAnswer(EBUTTONCOLOR::BLUE);
}

void UPuzzleSwitchWidget::OnGreenButtonClicked()
{
	Button_Green->SetIsEnabled(false);
	CheckPuzzleAnswer(EBUTTONCOLOR::GREEN);
}

void UPuzzleSwitchWidget::OnYellowButtonClicked()
{
	Button_Yellow->SetIsEnabled(false);
	CheckPuzzleAnswer(EBUTTONCOLOR::YELLOW);
}

void UPuzzleSwitchWidget::OnExitButtonClicked()
{
	ClearWidget();
}