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
	virtual FVector ConstrainInputAcceleration(const FVector& InputAcceleration) const;

	
};
