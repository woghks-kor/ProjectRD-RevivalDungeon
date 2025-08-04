// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "TriggerBoxComponent.generated.h"

/**
 *	다른 액터가 설정된 TargetActorTag 와 같은 Tag 를 가지고 있으면 이 트리거 박스에 붙임
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTRD_API UTriggerBoxComponent : public UBoxComponent
{
	GENERATED_BODY()
	
public:
	UTriggerBoxComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	USoundBase* StandSound;

	bool bIsStand = false;

public:
	UFUNCTION(BlueprintCallable)
	void SetMover(class UMoverComponent* Mover);

	UFUNCTION(BlueprintCallable)
	bool IsActorInTrigger() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* MoveActor;

private:
	UPROPERTY(EditAnyWhere)
	FName TargetActorTag;

	class UMoverComponent* Mover;

	AActor* GetAcceptableActor() const;
};
