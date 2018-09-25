// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "cppfpsGameMode.h"
#include "cppfpsHUD.h"
#include "cppfpsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AcppfpsGameMode::AcppfpsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AcppfpsHUD::StaticClass();
}
