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

void ABaseInteractableActor::OnInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("OnInteract"));
}

void ABaseInteractableActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Player = Cast<ACharacter>(OtherActor);
	if (!Player) return;

	if (bCanInteract)
	{
		SetHintMaterial(OutlineMaterial);

		if (WidgetClass)
		{
			InteractionWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
			if (!InteractionWidget) return;

			WidgetComp->SetWidget(InteractionWidget);
			WidgetComp->SetVisibility(true);
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
		SetHintMaterial(nullptr);

		if (InteractionWidget)
		{
			FTimerManager& TimerManager = GetWorld()->GetTimerManager();
			TimerManager.ClearTimer(TimerHandle);
			TimerManager.SetTimer(TimerHandle, this, &ABaseInteractableActor::ClearWidget, 0.15f);
		}
	}

	DisableInput(GetWorld()->GetFirstPlayerController());
}

void ABaseInteractableActor::CheckRepeat()
{
	if (!bShouldRepeatInteraction)
	{
		bCanInteract = false;
		SetHintMaterial(nullptr);
		ClearWidget();
		DisableInput(GetWorld()->GetFirstPlayerController());
	}
}

void ABaseInteractableActor::SetHintMaterial(UMaterialInterface* Material)
{
	if (bHintVisible)
	{
		bHintVisible = false;
		bCanPress = false;
	}
	else
	{
		bHintVisible = true;
		bCanPress = true;
	}

	MeshComp->SetOverlayMaterial(Material);
}

void ABaseInteractableActor::ClearWidget()
{
	InteractionWidget->RemoveFromParent();
	InteractionWidget = nullptr;
	WidgetComp->SetVisibility(false);
}
