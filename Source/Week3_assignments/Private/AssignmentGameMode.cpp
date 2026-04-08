// Fill out your copyright notice in the Description page of Project Settings.


#include "AssignmentGameMode.h"
#include "AssignmentsCharacter.h"
#include "AssignmentsPlayerController.h"

AAssignmentGameMode::AAssignmentGameMode() 
{
	DefaultPawnClass = AAssignmentsCharacter::StaticClass();
	PlayerControllerClass = AAssignmentGameMode::StaticClass();
}
