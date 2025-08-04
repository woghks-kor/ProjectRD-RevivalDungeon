// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/DialogueTriggerActor.h"

#include "Components/BoxComponent.h"
#include "BaseHintWidget.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ADialogueTriggerActor::ADialogueTriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComp;
}

// Called when the game starts or when spawned
void ADialogueTriggerActor::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ADialogueTriggerActor::OnBoxBeginOverlap);
	//BoxComp->OnComponentEndOverlap.AddDynamic(this, &ADialogueTriggerActor::OnBoxEndOverlap);
}

// Called every frame
void ADialogueTriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADialogueTriggerActor::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Player = Cast<ACharacter>(OtherActor);
	if (!Player) return;
	
	if (!WidgetClass) return;
	WidgetInstance = CreateWidget<UBaseHintWidget>(GetWorld(), WidgetClass);

	if (!WidgetInstance) return;
	WidgetInstance->ChangeHintImage(HintWidgetImage);
	WidgetInstance->AddToViewport();

	if (OverlapSound)
	{
		UGameplayStatics::PlaySound2D(this, OverlapSound);
	}

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.ClearTimer(TimerHandle);
	TimerManager.SetTimer(TimerHandle, this, &ADialogueTriggerActor::ClearWidget, DisplayTime);
}

void ADialogueTriggerActor::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ADialogueTriggerActor::ClearWidget()
{
	WidgetInstance->RemoveFromParent();
	Destroy();
}