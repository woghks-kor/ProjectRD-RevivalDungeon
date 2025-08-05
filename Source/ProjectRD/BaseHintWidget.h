// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseHintWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRD_API UBaseHintWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void ChangeHintImage(UTexture2D* NewDialogueTexture);

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* HintImage;
};
