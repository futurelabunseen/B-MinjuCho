// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CMGameInstance.h"
#include "CMSharedDefinition.h"

UCMGameInstance::UCMGameInstance()
{
	SetGameLevel(1);
	
	// Wait for Title
	IsSetTimerOn = true;
}

void UCMGameInstance::Init()
{
	Super::Init();
	LoadLevelDataFromJSON();
}

FCMLevelObjectiveData UCMGameInstance::GetObjectiveData(int32 Level) const
{
	if(Level > 0 && Level <= LevelsData.Num())
	{
		return LevelsData[Level - 1];
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid level: %d"), Level);
		return FCMLevelObjectiveData();
	}
}

void UCMGameInstance::LoadLevelDataFromJSON()
{
	FString JsonString;
	FString JsonFilePath = FPaths::ProjectContentDir() + "/Book/GameData/GameObjectivePerLevel.json";
    
	if (FFileHelper::LoadFileToString(JsonString, *JsonFilePath))
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

		if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
		{
			TArray<TSharedPtr<FJsonValue>> LevelsJsonArray = JsonObject->GetArrayField("levels");
            
			for (const auto& LevelJson : LevelsJsonArray)
			{
				FCMLevelObjectiveData LevelData;
				auto LevelObj = LevelJson->AsObject();

				LevelData.Level = LevelObj->GetIntegerField("level");
				LevelData.LimitTime = LevelObj->GetNumberField("limitTime");

				TArray<TSharedPtr<FJsonValue>> MonstersJsonArray = LevelObj->GetArrayField("monsters");
				for (const auto& MonsterJson : MonstersJsonArray)
				{
					FMonsterData MonsterData;
					auto MonsterObj = MonsterJson->AsObject();

					FGameplayTag MonsterTag = CMSharedDefinition::StringToMonsterTag(MonsterObj->GetStringField("monsterTag"));
					MonsterData.ColorTag = CMSharedDefinition::StringToColorTag(MonsterObj->GetStringField("colorTag"));
					MonsterData.MonsterNum = MonsterObj->GetIntegerField("monsterNum");

					LevelData.Monsters.Add(MonsterTag, MonsterData);
				}

				LevelsData.Add(LevelData);
			}

			UE_LOG(LogTemp, Log, TEXT("Successfully loaded %d levels from JSON"), LevelsData.Num());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON data"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load JSON file"));
	}
	DataNum = LevelsData.Num();
}
