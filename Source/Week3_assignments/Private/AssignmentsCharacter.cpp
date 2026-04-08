// Fill out your copyright notice in the Description page of Project Settings.


#include "AssignmentsCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "AssignmentsPlayerController.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAssignmentsCharacter::AAssignmentsCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;


	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	NormalSpeed = 600.0f;
	SprintSpeedMultiplier = 1.5f;
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;

}

// Called when the game starts or when spawned
void AAssignmentsCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAssignmentsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAssignmentsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		if (AAssignmentsPlayerController* PlayerController = Cast<AAssignmentsPlayerController>(GetController())) 
		{
			if (PlayerController->MoveAction)
			{
				// IA_Move 액션 키를 "키를 누르고 있는 동안" Move() 호출
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&AAssignmentsCharacter::Move
				);
			}

			if (PlayerController->JumpAction)
			{
				// IA_Move 액션 키를 "키를 누르고 있는 동안" Move() 호출
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered,
					this,
					&AAssignmentsCharacter::StartJump
				);

				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,
					this,
					&AAssignmentsCharacter::StopJump
				);
			}

			if (PlayerController->LookAction)
			{
				// IA_Move 액션 키를 "키를 누르고 있는 동안" Move() 호출
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AAssignmentsCharacter::Look
				);
			}

			if (PlayerController->SprintAction)
			{
				// IA_Move 액션 키를 "키를 누르고 있는 동안" Move() 호출
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Triggered,
					this,
					&AAssignmentsCharacter::StartSprint
				);

				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Completed,
					this,
					&AAssignmentsCharacter::StopSprint
				);
			}

		}
	}
}

void AAssignmentsCharacter::Move(const FInputActionValue& value)
{
	//2D Vector input
	if (!Controller) 
	{
		return;
	}
	const FVector2D MoveInput = value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}

	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}	 
	 
void AAssignmentsCharacter::StartJump(const FInputActionValue& value)
{
	//bool input 
	if (value.Get<bool>()) 
	{
		Jump();
	}
}	 
	 
void AAssignmentsCharacter::StopJump(const FInputActionValue& value)
{
	//bool input 
	if (value.Get<bool>())
	{
		StopJumping();
	}
}	 
	 
void AAssignmentsCharacter::Look(const FInputActionValue& value)
{
	//2D Vector input
	FVector2D LookInput = value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}	 
	 
void AAssignmentsCharacter::StartSprint(const FInputActionValue& value)
{	 
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}	 
	 
void AAssignmentsCharacter::StopSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}
}
