// Fill out your copyright notice in the Description page of Project Settings.

#include "BuiltPortal.h"
#include "ConstructorHelpers.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// visuals
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "cppfpsCharacter.h"
#include "cppfpsProjectile.h"
#include "DubDebug.h"

// Sets default values
ABuiltPortal::ABuiltPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = BoxComponent;
	BoxComponent->InitBoxExtent(FVector(90.0f,40.f,180.f));
	BoxComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
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

	PlaneVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentationPlane"));
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

	// ------ Rendering
	portalCaptureComponent= CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("captureComponent"));
	// Even though it's marked private in c++, it's a UPROPERTY so it's public
	portalCaptureComponent->bCaptureEveryFrame = true;
	portalCaptureComponent->SetupAttachment(RootComponent);
	portalRenderTarget = CreateDefaultSubobject<UTextureRenderTarget2D>(TEXT("portalRenderTarget"));
	portalRenderTarget->InitAutoFormat(1024, 1024);
	// Even though it's marked private in c++, it's a UPROPERTY so it's public
	portalCaptureComponent->TextureTarget = portalRenderTarget;
	
	static ConstructorHelpers::FObjectFinder<UMaterial> BaseMaterial(TEXT("/Game/PortalMaterial.PortalMaterial"));
	baseMaterial = BaseMaterial.Object;
}

// Called when the game starts or when spawned
void ABuiltPortal::BeginPlay()
{
	Super::BeginPlay();

	portalDynamicMaterial = PlaneVisual->CreateAndSetMaterialInstanceDynamicFromMaterial(0,baseMaterial);
	PlaneVisual->SetMaterial(0, portalDynamicMaterial);
	portalDynamicMaterial->SetTextureParameterValue("PortalTexture", portalRenderTarget);
}

// Called every frame
void ABuiltPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
#define DEBUG_PORTAL

void ABuiltPortal::OnTriggerOverlapBegin(class UPrimitiveComponent* Overlapped, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
#ifdef DEBUG_PORTAL
	printFString("Me = %s", *GetName());
	printFString("Other Actor = %s", *OtherActor->GetName());
#endif // DEBUG_PORTAL
	if (!endPortal->IsValidLowLevel())
		return;
	// don't run if not teleportable;
	if (!Cast<ITeleportable>(OtherActor))
		return;

	/* If we're the object's exit portal, don't teleport, and clear the destination portal. */
	ITeleportable* teleportable = Cast<ITeleportable>(OtherActor);
	if (teleportable->exitPortal==this) {
		teleportable->exitPortal = nullptr;
		return;
	}
	teleportable->exitPortal = endPortal;

	FTransform dest_transform = endPortal->GetTransform();
	FVector enter_offset = OtherActor->GetTransform().GetTranslation() - GetTransform().GetTranslation();

	/* get rotation between normal of this portal and out portal */
	FRotator deltaRotation = FRotator(0, 180, 0) - (GetActorRotation() - endPortal->GetActorRotation());

	/* add rotated offset to dest transform to get new player position */
	dest_transform.AddToTranslation(deltaRotation.RotateVector(enter_offset));

	OtherActor->TeleportTo(dest_transform.GetTranslation(), FRotator(0, 0, 0));
	OtherActor->UpdateComponentTransforms();
	//OtherActor->GetMove()->ComponentVelocity = deltaRotation.RotateVector(OtherActor->GetVelocity());
	// --------------------------------- if other object is player ---------------------------------
	if (OtherActor->GetClass()->IsChildOf(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetClass())) {
#ifdef DEBUG_PORTAL
		print("PC");
#endif // DEBUG_PORTAL
		AcppfpsCharacter* pc = (AcppfpsCharacter*)OtherActor;

		/* negate current velocity and new rotated velocity */
		((UCharacterMovementComponent*)(pc->GetMovementComponent()))->AddImpulse(
			-pc->GetVelocity() + deltaRotation.RotateVector(pc->GetVelocity())
			, true);
		// Removable?
		//pc->GetMovementComponent()->UpdateComponentVelocity();

		//pc->UpdateComponentTransforms();

		/* Don't change the controller (and camera's) rotation other than yaw */
		deltaRotation.Roll = 0;
		deltaRotation.Pitch = 0;

		pc->GetController()->SetControlRotation(
			pc->GetController()->GetControlRotation() + deltaRotation);
	}
	if (AcppfpsProjectile* p = Cast<AcppfpsProjectile>(OtherActor)) {
#ifdef DEBUG_PORTAL
		print("Proj");
#endif // DEBUG_PORTAL
		
		// while velocity is not marked as a public variable in the c++ code, it is a UProperty,
		// and as such, is marked public by unreal's preprocessor.
		// It's acceptable to access it here, as it's designed to be accessable in blueprints
		p->GetProjectileMovement()->Velocity = deltaRotation.RotateVector(p->GetVelocity());
	}
}


