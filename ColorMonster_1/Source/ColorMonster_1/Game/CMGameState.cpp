// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CMGameState.h"

#include "CMSharedDefinition.h"
#include "Game/CMGameInstance.h"
#include "Kismet/GameplayStatics.h"

ACMGameState::ACMGameState()
{
	PrimaryActorTick.bCanEverTick = false;
	Level = 1;
}

void ACMGameState::BeginPlay()
{
	Super::BeginPlay();

	// csv Data from GameInstance
	auto CMGameInstance = Cast<UCMGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(CMGameInstance)
	{
		
		if(CMGameInstance->GetObjectiveData(Level))
		{
			FInfoPerColor BaseInfo(CMGameInstance->GetObjectiveData(Level)->Base_Color, CMGameInstance->GetObjectiveData(Level)->Base_Number);

			GameObjective.Add(CM_MONSTER_BASE, BaseInfo);
			UpdateAllScoreUI();
		}
	}

}

void ACMGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

// Called By Monster Dead
void ACMGameState::UpdateFromDead(const FGameplayTag& Category, const FGameplayTag& Color)
{
	if(GameObjective.Contains(Category) && Color == GameObjective[Category].Color)
	{
		UpdateScoreData(Category, Color, GameObjective[Category].LeftOver - 1);
	}
}

// Update Partial Data
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
	if(CurrentMinute == 0 && CurrentSecond == 0)
	{
		GetWorldTimerManager().ClearTimer(TimeUpdateHandle);
	}
	OnTimeChanged.Broadcast(CurrentMinute, CurrentSecond);
}

void ACMGameState::SetTimerOn()
{
	// Timer Handler for Update Minute
	GetWorld()->GetTimerManager().SetTimer(TimeUpdateHandle, this, &ACMGameState::CalcMinute, 0.2f, true);
}
