// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CMPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "ColorMonster_1.h"

void ACMPlayerController::PostInitializeComponents()
{
	CM_LOG(LogCMNetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::PostInitializeComponents();

	CM_LOG(LogCMNetwork, Log, TEXT("%s"), TEXT("End"));
}

void ACMPlayerController::PostNetInit()
{
	CM_LOG(LogCMNetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::PostNetInit();

	UNetDriver* NetDriver = GetNetDriver();
	if (NetDriver)
	{
		if (NetDriver->ServerConnection)
		{
			CM_LOG(LogCMNetwork, Log, TEXT("Server Connection: %s"), *NetDriver->ServerConnection->GetName());
		}
	}
	else
	{
		CM_LOG(LogCMNetwork, Log, TEXT("%s"), TEXT("No NetDriver"));
	}

	CM_LOG(LogCMNetwork, Log, TEXT("%s"), TEXT("End"));
}

void ACMPlayerController::BeginPlay()
{
	CM_LOG(LogCMNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		//UE_LOG(LogTemp, Warning, TEXT("CMPlayerController BeginPlay"));
	}
	// 첫 화면은 UI이므로
	SetPlayerInputMode(false);

	CM_LOG(LogCMNetwork, Log, TEXT("%s"), TEXT("End"));
}

void ACMPlayerController::OnPossess(APawn* InPawn)
{
	CM_LOG(LogCMNetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::OnPossess(InPawn);

	CM_LOG(LogCMNetwork, Log, TEXT("%s"), TEXT("End"));
}

void ACMPlayerController::SetPlayerInputMode(bool bInputMode)
{
	FInputModeDataBase* InputMode = (bInputMode)
	? static_cast<FInputModeDataBase*>(new FInputModeGameOnly())
	: static_cast<FInputModeDataBase*>(new FInputModeUIOnly());

	SetInputMode(*InputMode);
	bShowMouseCursor = !bInputMode;
}
