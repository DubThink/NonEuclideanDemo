// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BuiltPortal.generated.h"


UCLASS()
class CPPFPS_API ABuiltPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuiltPortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UMaterial* baseMaterial;

	FVector LocationToExitSpace(FVector v);
	FRotator RotationToExitSpace(FRotator r);
	FRotator DeltaRotation();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// overlap begin function
	UFUNCTION()
	void OnTriggerOverlapBegin(class UPrimitiveComponent* Overlapped, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UPROPERTY(EditAnywhere)
	class ABuiltPortal* endPortal;
	// eventually make private - public for debugging
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PlaneVisual;
	UPROPERTY(EditAnywhere)
	class USceneCaptureComponent2D* portalCaptureComponent;
	UPROPERTY(EditAnywhere)
	class UTextureRenderTarget2D* portalRenderTarget;
	UPROPERTY(EditAnywhere)
	UMaterialInstanceDynamic* portalDynamicMaterial;
};
