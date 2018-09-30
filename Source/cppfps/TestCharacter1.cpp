// Fill out your copyright notice in the Description page of Project Settings.

#include "TestCharacter1.h"
#include "DubDebug.h"
#include "GameFramework/PhysicsVolume.h"

// Sets default values
ATestCharacter1::ATestCharacter1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestCharacter1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestCharacter1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//print("AAA");

}

// Called to bind functionality to input
void ATestCharacter1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn", this, &ATestCharacter1::testYaw);
	PlayerInputComponent->BindAxis("LookUp", this, &ATestCharacter1::testPitch);
	PlayerInputComponent->BindAxis("MoveForward", this, &ATestCharacter1::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATestCharacter1::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATestCharacter1::Jump);

}

void ATestCharacter1::testPitch(float d) {
	//print(FString::Printf(TEXT("Test pitch=%d"), d));
}

void ATestCharacter1::testYaw(float d) {
	//print(FString::Printf(TEXT("Test yaw=%d"), d));

}
void ATestCharacter1::MoveForward(float amt) {
	if (amt != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), amt);
		
	}
	print(FString::Printf(TEXT("Test forward=%f"), amt));

}

void ATestCharacter1::MoveRight(float amt) {
	if (amt != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorUpVector(), amt);

	}
	print(FString::Printf(TEXT("Test right=%f"), amt));

}
void ATestCharacter1::Jump() {
	GetPawnPhysicsVolume()->DisableComponentsSimulatePhysics();
	print("JUMP_________________");
}