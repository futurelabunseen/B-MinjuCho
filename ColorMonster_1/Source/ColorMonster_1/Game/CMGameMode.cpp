// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CMGameMode.h"

#include "CMGameState.h"
#include "UI/CMFPSHUD.h"
#include "UI/CMUserWidget.h"

ACMGameMode::ACMGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassRef(TEXT("/Game/Blueprint/BP_CMPlayer.BP_CMPlayer_C"));
	if (PlayerPawnClassRef.Class)
	{
		DefaultPawnClass = PlayerPawnClassRef.Class;
	}
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/ColorMonster_1.CMPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

	// UI
	static ConstructorHelpers::FClassFinder<ACMFPSHUD> HUDClassRef(TEXT("/Game/Blueprint/UI/BP_CMFPSHUD.BP_CMFPSHUD_C"));
	if (HUDClassRef.Class)
	{
		HUDClass = HUDClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UCMUserWidget> WBPClassRef(TEXT("/Game/Blueprint/UI/WBP_CM.WBP_CM_C"));
	if(WBPClassRef.Class)
	{
		WidgetClass = WBPClassRef.Class;
	}

	// Set GameState
	GameStateClass = ACMGameState::StaticClass();
}

void ACMGameMode::BeginPlay()
{
	Super::BeginPlay();

	if(WidgetClass)
	{
		UCMUserWidget* CMUserWidget = CreateWidget<UCMUserWidget>(GetWorld(), WidgetClass);
		if(CMUserWidget)
		{
			CMUserWidget->AddToViewport();
		}
	}
}
