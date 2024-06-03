// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CMSharedDefinition.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "CMGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FCMLevelObjectiveData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FCMLevelObjectiveData() : Level(1), Base_Color(CM_COLOR_RED), Base_Number(3) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FGameplayTag Base_Color;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Base_Number;

	// 몬스터 종류에 따라 확장 필요
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

	FCMLevelObjectiveData* GetObjectiveData(int32 Level) const;

private:
	UPROPERTY()
	TObjectPtr<class UDataTable> CMLevelObjectiveTable;
};
