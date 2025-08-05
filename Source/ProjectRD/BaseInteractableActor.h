// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseInteractableActor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractedDelegate);

UCLASS()
class PROJECTRD_API ABaseInteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseInteractableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void OnInteract();

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void CheckRepeat();

	void SetHintMaterial(UMaterialInterface* Material);

	UFUNCTION(BlueprintCallable)
	void ClearWidget();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanInteract = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldRepeatInteraction = true;

	UPROPERTY()
	bool bHintVisible = false;

	UPROPERTY(BlueprintReadWrite)
	bool bCanPress = false;

public:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* WidgetComp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WidgetClass;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* OutlineMaterial;

	FTimerHandle TimerHandle;

	UPROPERTY(BlueprintAssignable)
	FOnInteractedDelegate OnInteractDelegate;
};
