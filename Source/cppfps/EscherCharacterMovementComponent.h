// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EscherCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class CPPFPS_API UEscherCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	UEscherCharacterMovementComponent(const FObjectInitializer& ObjectInitializer);

	virtual FVector ConstrainInputAcceleration(const FVector& InputAcceleration) const;

	//PhysFalling
	virtual void PhysFalling(float deltaTime, int32 Iterations) override;

	//virtual void PhysFalling(float deltaTime, int32 Iterations);
	virtual FVector GetFallingLateralAcceleration(float DeltaTime);
};
