// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CMGameMode.h"

#include "GameFramework/HUD.h"
#include "UI/CMFPSHUD.h"

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

	static ConstructorHelpers::FClassFinder<ACMFPSHUD> HUDClassRef(TEXT("/Game/Blueprint/BP_CMFPSHUD.BP_CMFPSHUD_C"));
	if (HUDClassRef.Class)
	{
		HUDClass = HUDClassRef.Class;
	}
	// TSubclassOf<Derieved> -> Available Downcasting 
}
