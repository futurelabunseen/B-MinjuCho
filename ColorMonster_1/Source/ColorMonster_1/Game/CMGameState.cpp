// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CMGameState.h"

#include "CMSharedDefinition.h"
#include "Game/CMGameInstance.h"
#include "Kismet/GameplayStatics.h"

ACMGameState::ACMGameState()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACMGameState::BeginPlay()
{
	Super::BeginPlay();
}

void ACMGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACMGameState::InitializeScoreData(int32 Level)
{
	// csv Data from GameInstance
	auto CMGameInstance = Cast<UCMGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(CMGameInstance)
	{
		if(CMGameInstance->GetObjectiveData(Level))
		{
			GameObjective.Reset();
			FInfoPerColor BaseInfo(CMGameInstance->GetObjectiveData(Level)->Base_Color, CMGameInstance->GetObjectiveData(Level)->Base_Number);

			GameObjective.Emplace(CM_MONSTER_BASE, BaseInfo);
			UpdateAllScoreUI();
		}
	}
}

// Called By Monster Dead
void ACMGameState::UpdateFromDead(const FGameplayTag& Category, const FGameplayTag& Color)
{
	if(GameObjective.Contains(Category) && Color == GameObjective[Category].Color)
	{
		UpdateScoreData(Category, Color, GameObjective[Category].LeftOver - 1);
	}
}

// 몬스터 하나 죽일 때마다 불리는 Update Partial Data
void ACMGameState::UpdateScoreData(const FGameplayTag& Category, const FGameplayTag& Color, int32 Number)
{
	FInfoPerColor BaseInfo(Color, Number);
	if(GameObjective.Contains(Category))
	{
		GameObjective[Category] = BaseInfo;
	}
	else
	{
		GameObjective.Add(Category, BaseInfo);
	}
	UpdateScoreUI(Category);

	// 한 목표를 0으로 만들었을 때 목표 완수 계산
	if(Number <= 0)
	{
		if(CalculateWin())
		{
			GameOver();
		}
	}
}

// Update All Data
void ACMGameState::UpdateAllScoreUI() const
{
	for(auto ElemOfObjective : GameObjective)
	{
		UpdateScoreUI(ElemOfObjective.Key);
	}
}

// Broadcast to CMUserWidget
void ACMGameState::UpdateScoreUI(const FGameplayTag& Monster) const
{
	FText MonsterKey = CMSharedDefinition::MonsterTagToText(Monster);
	FText ColorValue = CMSharedDefinition::ColorTagToText(GameObjective[Monster].Color);
	FText NumberValue = FText::AsNumber(GameObjective[Monster].LeftOver);
	OnScoreChanged.Broadcast(MonsterKey, ColorValue, NumberValue);
}

void ACMGameState::CalcMinute()
{
	CurrentMinute = CurrentLeftTime / 60;
	CurrentSecond = static_cast<int>(CurrentLeftTime) % 60;
	// 타이머가 끝났을 때 목표 완수 계산
	if(CurrentMinute == 0 && CurrentSecond == 0)
	{
		GameOver();
	}
	OnTimeChanged.Broadcast(CurrentMinute, CurrentSecond);
}

void ACMGameState::GameOver()
{
	// Stop Timer
	GetWorldTimerManager().ClearTimer(TimeUpdateHandle);
	if(CalculateWin() == true)
	{
		// Win UI
		OnWinWindowChanged.Broadcast(true);
		OnLooseWindowChanged.Broadcast(false);
	}
	else
	{
		// Loose UI
		OnWinWindowChanged.Broadcast(false);
		OnLooseWindowChanged.Broadcast(true);
	}
}

// 목표 완수 계산
bool ACMGameState::CalculateWin() const
{
	for(auto ElemOfObjective : GameObjective)
	{
		if(ElemOfObjective.Value.LeftOver != 0)
		{
			return false;
		}
	}
	return true;
}

void ACMGameState::SetTimerOn()
{
	// Timer Handler for Update Minute
	GetWorld()->GetTimerManager().SetTimer(TimeUpdateHandle, this, &ACMGameState::CalcMinute, 0.2f, true);
}
