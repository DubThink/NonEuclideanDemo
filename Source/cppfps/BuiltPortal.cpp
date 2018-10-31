// Fill out your copyright notice in the Description page of Project Settings.

#include "BuiltPortal.h"
#include "ConstructorHelpers.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "cppfpsCharacter.h"
#include "DubDebug.h"
// Sets default values
ABuiltPortal::ABuiltPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = BoxComponent;
	BoxComponent->InitBoxExtent(FVector(90.0f,40.f,180.f));
	BoxComponent->SetCollisionProfileName(TEXT("Trigger"));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABuiltPortal::OnTriggerOverlapBegin);

	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentationSphere"));
	SphereVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}
	SphereVisual->SetCollisionProfileName(TEXT("NoCollision"));

	UStaticMeshComponent* PlaneVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentationPlane"));
	PlaneVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane"));
	if (PlaneVisualAsset.Succeeded())
	{
		PlaneVisual->SetStaticMesh(PlaneVisualAsset.Object);
		//SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		PlaneVisual->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
		PlaneVisual->SetWorldScale3D(FVector(1.8f, 3.5f, 1.0f));
	}
	PlaneVisual->SetCollisionProfileName(TEXT("NoCollision"));
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

void ABuiltPortal::OnTriggerOverlapBegin(class UPrimitiveComponent* Overlapped, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	printFString("Me = %s", *GetName());
	printFString("Other Actor = %s", *OtherActor->GetName());
	if (OtherActor->GetClass()->IsChildOf(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetClass())
		&& endPortal->IsValidLowLevel()) {
		print("PC");
		AcppfpsCharacter* pc = (AcppfpsCharacter*)OtherActor;
		/* Don't teleport if already teleported this frame. */
		if (pc->teleportedThisFrame)return;
		pc->teleportedThisFrame = true;
		FTransform dest_transform = endPortal->GetTransform();
		FVector enter_offset = pc->GetTransform().GetTranslation() - GetTransform().GetTranslation();
		FRotator deltaRotation = GetActorRotation() - endPortal->GetActorRotation();
		
		dest_transform.AddToTranslation(deltaRotation.RotateVector(enter_offset));
		
		//printFString("dest_transform = %s", *dest_transform.ToHumanReadableString());
		pc->TeleportTo(dest_transform.GetTranslation(), FRotator(0,0,0));
		pc->GetController()->GetParentComponent();//SetControlRotation(FRotator(0, 25, 25));
		pc->UpdateComponentTransforms();
		//UMovementComponent* pc_move=pc->GetMovementComponent();
		//pc_move->MoveUpdatedComponent(FVector(0,0,0), FRotator(0, 25, 25),false);
		//	SetActorRelativeRotation(FRotator(0, 25, 25));
		pc->GetController()->SetControlRotation(
			pc->GetController()->GetControlRotation() +deltaRotation);
		//pc->GetMovementBaseActor()->SetVelocity()(pc->GetVelocity();
		//print("TP old:");
		//print(pc->GetVelocity().ToCompactString());
		//print("TP new:");
		//print(deltaRotation.RotateVector(pc->GetVelocity()).ToCompactString());
		//print(deltaRotation.ToCompactString());

		//pc->AddMovementInput(,1.0f,true);
		((UCharacterMovementComponent*)(pc->GetMovementComponent()))->AddImpulse(
			-pc->GetVelocity() + deltaRotation.RotateVector(pc->GetVelocity())
		,true);
		//	deltaRotation.GetInverse().RotateVector( -pc->GetVelocity() )//pc->GetVelocity())//
		//);
		pc->GetMovementComponent()->UpdateComponentVelocity();
		//pc->doTilt();//SetActorRotation(FRotator(0, 25, 25));
		//APlayerController* pc_controller=UGameplayStatics::GetPlayerController(GetWorld(), 0);
		//pc_controller->SetControlRotation(FRotator(0, 0, 0));
	}

}


