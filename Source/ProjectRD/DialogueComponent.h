// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueChanged, UTexture2D*, NewDialogue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueFinished);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTRD_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogueComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<TObjectPtr<class UTexture2D>> DialogueImages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TSubclassOf<class UBaseDialogueWidget> DialogueWidgetClass;

	UPROPERTY(BlueprintAssignable, Category = "Dialogue")
	FOnDialogueChanged OnDialogueChanged;

	UPROPERTY(BlueprintAssignable, Category = "Dialogue")
	FOnDialogueFinished OnDialogueFinished;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void CreateDialogueWidget();

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void StartDialogue();

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void NextDialogue();

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void FinishDialogue();

protected:
	int32 CurrentIndex = 0;
		
};
