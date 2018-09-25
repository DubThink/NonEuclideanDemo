// Fill out your copyright notice in the Description page of Project Settings.

#include "BuiltPortal.h"
#include "ConstructorHelpers.h"
#include "Components/BoxComponent.h"


// Sets default values
ABuiltPortal::ABuiltPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = BoxComponent;
	BoxComponent->InitBoxExtent(FVector(40.0f,40.f,40.f));
	BoxComponent->SetCollisionProfileName(TEXT("Pawn"));

	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}

}

// Called when the game starts or when spawned
void ABuiltPortal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuiltPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

