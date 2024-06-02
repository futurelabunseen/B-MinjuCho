// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CMGameState.h"

#include "CMSharedDefinition.h"

ACMGameState::ACMGameState()
{
	PrimaryActorTick.bCanEverTick = true;

	
	FInfoPerColor BaseInfo(CM_COLOR_RED, 3);
	GameObjective.Add(CM_MONSTER_BASE, BaseInfo);
}

void ACMGameState::BeginPlay()
{
	Super::BeginPlay();
	UpdateAllScoreUI();
}

void ACMGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACMGameState::UpdateFromDead(const FGameplayTag& Category, const FGameplayTag& Color)
{
	if(GameObjective.Contains(Category))
	{
		UpdateScoreData(Category, Color, GameObjective[Category].LeftOver - 1);
	}
}

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

void ACMGameState::UpdateAllScoreUI() const
{
	for(auto ElemOfObjective : GameObjective)
	{
		UpdateScoreUI(ElemOfObjective.Key);
	}
}

void ACMGameState::UpdateScoreUI(const FGameplayTag& Monster) const
{
	FText MonsterKey = CMSharedDefinition::MonsterTagToText(Monster);
	FText ColorValue = CMSharedDefinition::ColorTagToText(GameObjective[Monster].Color);
	FText NumberValue = FText::AsNumber(GameObjective[Monster].LeftOver);
	OnScoreChanged.Broadcast(MonsterKey, ColorValue, NumberValue);
}
