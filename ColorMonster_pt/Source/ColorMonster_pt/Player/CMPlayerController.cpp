// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CMPlayerController.h"

void ACMPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
}
