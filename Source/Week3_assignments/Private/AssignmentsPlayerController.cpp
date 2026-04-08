// Fill out your copyright notice in the Description page of Project Settings.


#include "AssignmentsPlayerController.h"
#include "EnhancedInputSubsystems.h"

AAssignmentsPlayerController::AAssignmentsPlayerController() 
	: InputMappingContext(nullptr),
    MoveAction(nullptr),
    JumpAction(nullptr),
    LookAction(nullptr),
    SprintAction(nullptr)
{

}

void AAssignmentsPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (ULocalPlayer* LocalPlayer = GetLocalPlayer()) 
    {
        if (UEnhancedInputLocalPlayerSubsystem* SubSytem =
            LocalPlayer->GetSubsystem< UEnhancedInputLocalPlayerSubsystem>()) 
        {
            if (InputMappingContext) 
            {
                SubSytem->AddMappingContext(InputMappingContext, 0);
            }
        }
    }
}
