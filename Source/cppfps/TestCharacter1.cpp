// Fill out your copyright notice in the Description page of Project Settings.

#include "TestCharacter1.h"
#include "DubDebug.h"
#include "GameFramework/PhysicsVolume.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"
#include "EscherCharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

#define DEG_TO_RAD 0.0174533
// Sets default values
ATestCharacter1::ATestCharacter1(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UEscherCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera

}

// Called when the game starts or when spawned
void ATestCharacter1::BeginPlay()
{
	Super::BeginPlay();
	//this->bUseControllerRotationPitch
	//SetActorRotation(FRotator(0, 45, 0));
}

// Called every frame
void ATestCharacter1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//auto a = GetOwner();
	GetController()->SetControlRotation(FRotator(50, 0, 0));
	
	//AddMovementInput(FVector(-1.0f,0.0f,1.0f), 1.0f);
	//AddActorWorldRotation(FQuat(GetActorUpVector(), 0.001f));
	//print(GetActorUpVector().ToCompactString());
	//print("AAA");
	//AddActorLocalRotation(FRotator(0, 0.2f, 0));
	//BaseRotationOffset

}

// Called to bind functionality to input
void ATestCharacter1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn", this, &ATestCharacter1::testYaw);
	PlayerInputComponent->BindAxis("LookUp", this, &ATestCharacter1::testPitch);
	PlayerInputComponent->BindAxis("MoveForward", this, &ATestCharacter1::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATestCharacter1::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

}

void ATestCharacter1::testPitch(float d) {
	//print(FString::Printf(TEXT("Test pitch=%f"), d));
	yRot += d;
	//FirstPersonCameraComponent->AddLocalRotation(FRotator(-d, 0, 0));
}

void ATestCharacter1::testYaw(float d) {
	//print(FString::Printf(TEXT("Test yaw=%d"), d));
	//auto x = FQuat(GetActorUpVector(), d*DEG_TO_RAD);
	//auto x = FQuat(FRotator(0,d,0));
	/*print(x.GetAxisX().ToCompactString());
	print(x.GetAxisY().ToCompactString());
	print(x.GetAxisZ().ToCompactString());*/
	//FRotator rotator = FRotator(0, 20, 0);
	//SetActorRotation(rotator);
	xRot += d;
	//FirstPersonCameraComponent->SetRelativeRotation(FRotator(-yRot, xRot, 0));
	//FRotator rot=FirstPersonCameraComponent
	//FirstPersonCameraComponent->SetRelativeLocationAndRotation(
	//	FVector(0,0,0),
	//	FRotator(-d, 0, 0));

}
void ATestCharacter1::MoveForward(float amt) {
	if (amt != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), amt);
		
	}
	//print(FString::Printf(TEXT("Test forward=%f"), amt));

}

void ATestCharacter1::MoveRight(float amt) {
	if (amt != 0.0f)
	{
		print(FString::Printf(TEXT("amt=%.6f"), amt));
		if (amt > 0) {
			Controller->SetControlRotation(FRotator(45, 45, 0));
			print("setting rot");
		}
		else {
			//SetActorRotation(FRotator(0, 0, 0));
			//SetActorRotation(FRotator(50, 0, 0));
			Controller->SetControlRotation(FRotator(0, 0, 0));

			print("clearing rot ");
		}
		// add movement in that direction
		//AddMovementInput(GetActorUpVector(), amt);


	}
	//print(FString::Printf(TEXT("Test right=%f"), amt));

}
//void ATestCharacter1::Jump() {
//	GetPawnPhysicsVolume()->DisableComponentsSimulatePhysics();
//	print("JUMP_________________");
//}