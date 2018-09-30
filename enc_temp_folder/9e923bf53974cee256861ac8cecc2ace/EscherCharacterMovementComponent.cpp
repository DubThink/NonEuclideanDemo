// Fill out your copyright notice in the Description page of Project Settings.

#include "EscherCharacterMovementComponent.h"

FVector UEscherCharacterMovementComponent::ConstrainInputAcceleration(const FVector& InputAcceleration) const
{
	// walking or falling pawns ignore up/down sliding
	//if (InputAcceleration.Z != 0.f && (IsMovingOnGround() || IsFalling()))
	//{
	//	return FVector(InputAcceleration.X, InputAcceleration.Y, 0.f);
	//}

	return InputAcceleration;
}


