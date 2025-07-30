// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInteractableActor.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"


// Sets default values
ABaseInteractableActor::ABaseInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComp->SetupAttachment(MeshComp);

	SphereComp->SetSphereRadius(300.f);

	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComp->SetupAttachment(MeshComp);
	WidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
}

// Called when the game starts or when spawned
void ABaseInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABaseInteractableActor::OnSphereBeginOverlap);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &ABaseInteractableActor::OnSphereEndOverlap);
}

// Called every frame
void ABaseInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseInteractableActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Player = Cast<ACharacter>(OtherActor);
	if (!Player) return;

	if (bCanInteract)
	{
		if (WidgetClass)
		{
			InteractionWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
			if (!InteractionWidget) return;

			WidgetComp->SetWidget(InteractionWidget);
			WidgetComp->SetVisibility(true);
		}

		if (!bHintVisible)
		{
			MeshComp->SetOverlayMaterial(OutlineMaterial);

			bHintVisible = true;
			bCanPress = true;
		}
	}

	EnableInput(GetWorld()->GetFirstPlayerController());
}

void ABaseInteractableActor::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter* Player = Cast<ACharacter>(OtherActor);
	if (!Player) return;

	if (bCanInteract)
	{
		if (bHintVisible)
		{
			MeshComp->SetOverlayMaterial(nullptr);

			bHintVisible = false;
			bCanPress = false;
		}

		if (InteractionWidget)
		{
			FTimerManager& TimerManager = GetWorld()->GetTimerManager();
			TimerManager.ClearTimer(TimerHandle);
			TimerManager.SetTimer(TimerHandle, this, &ABaseInteractableActor::ClearWidget, 0.15f);
		}
	}

	DisableInput(GetWorld()->GetFirstPlayerController());
}

void ABaseInteractableActor::ClearWidget()
{
	InteractionWidget->RemoveFromParent();
	InteractionWidget = nullptr;
	WidgetComp->SetVisibility(false);
}
