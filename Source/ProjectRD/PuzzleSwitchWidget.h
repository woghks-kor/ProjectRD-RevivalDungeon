// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PuzzleSwitchWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPuzzleSuccess);

UENUM(BlueprintType)
enum class EBUTTONCOLOR : uint8
{
	RED UMETA(DisplayName = "Red"),
	BLUE UMETA(DisplayName = "Blue"),
	GREEN UMETA(DisplayName = "Green"),
	YELLOW UMETA(DisplayName = "Yellow")
};

/**
 * 
 */
UCLASS()
class PROJECTRD_API UPuzzleSwitchWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

public:
	//void StartPuzzle();
	void CheckPuzzleAnswer(EBUTTONCOLOR Color);
	void ResetPuzzle();
	void ClearWidget();

public:
	UPROPERTY(BlueprintAssignable, Category = "Puzzle")
	FOnPuzzleSuccess OnPuzzleSuccess;

	FTimerHandle TimerHandle;

public:
	int32 Count = 0;

	UPROPERTY(EditAnywhere, Category = "Puzzle")
	EBUTTONCOLOR Answer[4] = { 
		EBUTTONCOLOR::RED, EBUTTONCOLOR::YELLOW, EBUTTONCOLOR::BLUE, EBUTTONCOLOR::GREEN };

	// 5개 이미지 (0개, 1개, 2개, 3개, 4개 정답)
	UPROPERTY(EditAnywhere, Category = "Puzzle")
	TArray<TObjectPtr<class UTexture2D>> CountImages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	USoundBase* ClickSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	USoundBase* AnswerSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	USoundBase* WrongSound;

protected:
	UFUNCTION()
	void OnRedButtonClicked();

	UFUNCTION()
	void OnBlueButtonClicked();

	UFUNCTION()
	void OnGreenButtonClicked();

	UFUNCTION()
	void OnYellowButtonClicked();

	UFUNCTION()
	void OnExitButtonClicked();

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Exit;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Red;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Blue;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Green;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Yellow;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Background;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Count;
};
