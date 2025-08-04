// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHintWidget.h"

#include "Components/Image.h"


void UBaseHintWidget::ChangeHintImage(UTexture2D* NewDialogueTexture)
{
	if (!NewDialogueTexture) return;
	HintImage->SetBrushFromTexture(NewDialogueTexture);
}
