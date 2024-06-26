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
	UE_LOG(LogTemp, Warning, TEXT("ACMGameState::InitializeScoreData %d"), Level);
	// csv Data from GameInstance
	auto CMGameInstance = Cast<UCMGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(CMGameInstance)
	{
		if(Level > 0 && Level <= CMGameInstance->GetDataNum())
		{
			GameObjective.Reset();

			// 각 몬스터 별로 저장.
			FCMLevelObjectiveData ObjectiveData = CMGameInstance->GetObjectiveData(Level);
			for(const TPair<FGameplayTag, FMonsterData>& Monster : ObjectiveData.Monsters)
			{
				FInfoPerMonster BaseInfo(Monster.Value.ColorTag, Monster.Value.MonsterNum);
				GameObjective.Emplace(Monster.Key, BaseInfo);
				UE_LOG(LogTemp, Warning, TEXT("ACMGameState::InitializeScoreData %s %s %d"), *Monster.Key.ToString(), *BaseInfo.Color.ToString(), BaseInfo.LeftOver);
			}
			
			
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
		
		UE_LOG(LogTemp, Warning, TEXT("ACMGameState::UpdateFromDead"));
	}
}

// 몬스터 하나 죽일 때마다 불리는 Update Partial Data
void ACMGameState::UpdateScoreData(const FGameplayTag& Category, const FGameplayTag& Color, int32 Number)
{
	FInfoPerMonster BaseInfo(Color, Number);
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
	UE_LOG(LogTemp, Warning, TEXT("ACMGameState::UpdateScoreUI"));
	FText MonsterKey = CMSharedDefinition::MonsterTagToText(Monster);
	FText ColorValue = CMSharedDefinition::ColorTagToText(GameObjective[Monster].Color);
	FText NumberValue = FText::AsNumber(GameObjective[Monster].LeftOver);
	OnScoreChanged.Broadcast(MonsterKey, ColorValue, NumberValue);
}

void ACMGameState::CalcMinute()
{
	// 0.2초마다 GameMode에서 넘어온 값으로 시간 계산
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
	// 이미 게임 오버 판정 났을 때는 중복 호출 막기.
	if(GetIsCleared() == true)
	{
		return;
	}
	SetIsCleared(true);
	
	// Stop Timer
	SetTimerOff();
	
	if(CalculateWin() == true)
	{
		// Win UI
		OnWinWindowChanged.Broadcast(true);
		//OnLooseWindowChanged.Broadcast(false);
	}
	else
	{
		// Loose UI
		//OnWinWindowChanged.Broadcast(false);
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
	UE_LOG(LogTemp, Warning, TEXT("ACMGameState::SetTimerOn()"));
	// Timer Handler for Update Minute
	GetWorld()->GetTimerManager().SetTimer(TimeUpdateHandle, this, &ACMGameState::CalcMinute, 1.2f, true);
}

void ACMGameState::SetTimerOff()
{
	if(TimeUpdateHandle.IsValid())
	{
		// Stop Timer
		UE_LOG(LogTemp, Warning, TEXT("ACMGameState::SetTimerOff()"));
		GetWorldTimerManager().PauseTimer(TimeUpdateHandle);
		GetWorldTimerManager().ClearTimer(TimeUpdateHandle);
	}
}

void ACMGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}
