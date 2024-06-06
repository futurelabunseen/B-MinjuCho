// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CMGameInstance.h"

UCMGameInstance::UCMGameInstance()
{
	// Load CSV Data
	FString ObjectiveDataPath = TEXT("/Game/Book/GameData/GameObjectivePerLevel.GameObjectivePerLevel");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CMOBJECTIVE(*ObjectiveDataPath);
	if(DT_CMOBJECTIVE.Object)
	{
		CMLevelObjectiveTable = DT_CMOBJECTIVE.Object;
	}
	// Check Valid Data
	ensure(CMLevelObjectiveTable->GetRowMap().Num() > 0);

}

void UCMGameInstance::Init()
{
	Super::Init();
}

FCMLevelObjectiveData* UCMGameInstance::GetObjectiveData(int32 Level) const
{
	return CMLevelObjectiveTable->FindRow<FCMLevelObjectiveData>(*(FString::FromInt(Level)), TEXT(""));
}
