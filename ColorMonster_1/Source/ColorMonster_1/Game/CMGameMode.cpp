// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CMGameMode.h"

#include "Game/CMGameInstance.h"
#include "CMGameState.h"
#include "Kismet/GameplayStatics.h"
#include "UI/CMFPSHUD.h"
#include "UI/CMUserWidget.h"

ACMGameMode::ACMGameMode()
{
	// For Time
	PrimaryActorTick.bCanEverTick = true;

	// Player Setting
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

	// static ConstructorHelpers::FClassFinder<UCMUserWidget> WBPClassRef(TEXT("/Game/Blueprint/UI/WBP_CM.WBP_CM_C"));
	// if(WBPClassRef.Class)
	// {
	// 	WidgetClass = WBPClassRef.Class;
	// }

	// Set GameInstance, GameState
	CMGameInstance = Cast<UCMGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameStateClass = ACMGameState::StaticClass();
	

	// Wait for Title
	IsSetTimerOn = true;
	// First
	GameLevel = -1;
}

void ACMGameMode::BeginPlay()
{
	Super::BeginPlay();

	ensure(CMGameInstance);
	//GameLevel = CMGameInstance->GetGameLevel();

	// Set GameState
	CMGameState = GetWorld()->GetGameState<ACMGameState>();
	ensure(CMGameState);
	CMGameState->InitializeScoreData(CMGameInstance->GetGameLevel());
}

void ACMGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateTime(DeltaSeconds);
}

void ACMGameMode::UpdateTime(float DeltaSeconds)
{
	if(IsSetTimerOn == false)
	{
		IsSetTimerOn = true;
		InitializeTime();
		CMGameState->SetTimerOn();
	}
	if(CurrentLeftTime <= KINDA_SMALL_NUMBER)
	{
		return;
	}
	else
	{
		CurrentLeftTime -= DeltaSeconds;
		CMGameState->SetCurrentLeftTime(CurrentLeftTime);
	}
}

void ACMGameMode::InitializeTime()
{
	if(CMGameInstance == nullptr)
	{
		CMGameInstance = Cast<UCMGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}
	if(CMGameInstance)
	{
		LimitTimePerThisLevel = GetLimitTime();
	}
	CurrentLeftTime = LimitTimePerThisLevel;
}

// Get Data From GameInstance
float ACMGameMode::GetLimitTime() const
{
	ensure(CMGameInstance);
	return CMGameInstance->GetObjectiveData(CMGameInstance->GetGameLevel()).LimitTime;
}

void ACMGameMode::SetLevelAndLoad(int32 InLevel = -1)
{
	UE_LOG(LogTemp, Warning, TEXT("InLevel: %d, CMGameInstance->GetGameLevel() : %d"), InLevel, CMGameInstance->GetGameLevel());
	ensure(CMGameInstance);
	if(InLevel == CMGameInstance->GetGameLevel())
	{
		// Update Game Objective passing to GameState
		CMGameState->InitializeScoreData(CMGameInstance->GetGameLevel());
		IsSetTimerOn = false;
		RestartGame();
		return;
	}
	
	// Default: Next Level
	if(InLevel == -1)
	{
		CMGameInstance->SetGameLevel(CMGameInstance->GetGameLevel() + 1);
	}
	else
	{
		CMGameInstance->SetGameLevel(InLevel);
	}
	GameLevel = CMGameInstance->GetGameLevel();
	// Update Game Objective passing to GameState
	CMGameState->InitializeScoreData(CMGameInstance->GetGameLevel());
	IsSetTimerOn = false;
	// 멀티 환경에서 클라이언트끼리 스타트 시점 맞추기 위해서 Delay Start 사용할 때 게임모드 전환이 필요하다.
	// 게임모드 기능 활용하면 손봐야하고, 아니면 타이머로 구현 가능
	
}

