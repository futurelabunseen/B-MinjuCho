// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CMSharedDefinition.h"
#include "SkeletalMeshAttributes.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "CMGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FMonsterData
{
	GENERATED_BODY()

public:
	FMonsterData() : ColorTag(CM_COLOR_RED), MonsterNum(3) {}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FGameplayTag ColorTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
	int32 MonsterNum;
};

USTRUCT(BlueprintType)
struct FCMLevelObjectiveData
{
	GENERATED_BODY()
	
public:
	FCMLevelObjectiveData() : Level(1), LimitTime(180.0f)
	{Monsters.Add(CM_MONSTER_BASE, FMonsterData());}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float LimitTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TMap<FGameplayTag, FMonsterData> Monsters;
};

/**
 * 
 */
UCLASS()
class COLORMONSTER_1_API UCMGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCMGameInstance();
	virtual void Init() override;

	UFUNCTION()
	FCMLevelObjectiveData GetObjectiveData(int32 Level) const;

public:
	int32 GetGameLevel() const {return GameLevel;}
	void SetGameLevel(int32 InLevel) {GameLevel = InLevel;}
	
	int32 GetDataNum() const {return DataNum;}

private:
	UPROPERTY()
	TArray<FCMLevelObjectiveData> LevelsData;

	void LoadLevelDataFromJSON();

// Keep Level Without Converting Map
	UPROPERTY()
	int32 GameLevel;

	UPROPERTY()
	int32 DataNum;
};
