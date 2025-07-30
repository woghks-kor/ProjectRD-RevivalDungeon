// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseDialogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRD_API UBaseDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

protected:
	UFUNCTION()
	void OnNextButtonClicked();

	UFUNCTION()
	void OnExitButtonClicked();

	UFUNCTION()
	void OnDialogueChanged(UTexture2D* NewDialogueTexture);

	UFUNCTION()
	void OnDialogueFinished();

	void SetInputModeGameAndUI();
	void SetInputModeGameOnly();

public:
	UPROPERTY(BlueprintReadWrite)
	class UDialogueComponent* DialogueComp;

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Next;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Exit;

	UPROPERTY(meta = (BindWidget))
	class UImage* DialogueImage;
};
