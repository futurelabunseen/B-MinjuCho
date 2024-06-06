// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CMSharedDefinition.h"
#include "CMGameMode.generated.h"

/**
 * 
 */
UCLASS()
class COLORMONSTER_1_API ACMGameMode : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	ACMGameMode();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

// Time
private:
	void UpdateTime(float DeltaSeconds);

	UPROPERTY()
	float LimitTimePerThisLevel;
	
	UPROPERTY()
	float CurrentLeftTime;
public:
	void InitializeTime();

// UI
private:
	UPROPERTY(EditAnywhere, Blueprintable, Category = "UI")
	TSubclassOf<UUserWidget> WidgetClass;

// GameObjectData
public:
	int32 GetGameLevel() const;
	float GetLimitTime() const;
	FGameplayTag GetBaseColor() const;
	int32 GetBaseNumber() const;

private:
	UPROPERTY()
	TObjectPtr<class UCMGameInstance> CMGameInstance;

	UPROPERTY()
	TObjectPtr<class ACMGameState> CMGameState;

	UPROPERTY()
	int32 GameLevel;
	
	void SetGameLevel(int32 InLevel);

	UPROPERTY()
	bool IsSetTimerOn = false;
// Need Setting Next Level
public:
	
};
