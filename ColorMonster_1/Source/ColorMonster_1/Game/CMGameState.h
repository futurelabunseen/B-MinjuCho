// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "CMSharedDefinition.h"
#include "CMGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnScoreChanged, const FText&, Monster, const FText&, Color, const FText&, Number);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTimeChanged, int32, Minute, int32, Second);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWinWindowChanged, bool, IsTurnOn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLooseWindowChanged, bool, IsTurnOn);

/**
 * 
 */
UCLASS()
class COLORMONSTER_1_API ACMGameState : public AGameState
{
	GENERATED_BODY()

public:
	ACMGameState();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION()
	void InitializeScoreData(int32 Level);

	UFUNCTION()
	void UpdateFromDead(const FGameplayTag& Category, const FGameplayTag& Color);
	
	// Delagate Instance
	FOnScoreChanged OnScoreChanged;
	FOnTimeChanged OnTimeChanged;
	FOnWinWindowChanged OnWinWindowChanged;
	FOnLooseWindowChanged OnLooseWindowChanged;

	float GetCurrentLeftTime() const { return CurrentLeftTime; }
	void SetCurrentLeftTime(float InTime) { CurrentLeftTime = InTime; }

// Score
private:	
	UFUNCTION()
	void UpdateScoreData(const FGameplayTag& Category, const FGameplayTag& Color, int32 Number);
	
	UFUNCTION()
	void UpdateAllScoreUI() const;

	UFUNCTION()
	void UpdateScoreUI(const FGameplayTag& Monster) const;
	
	UPROPERTY()
	TMap<FGameplayTag, FInfoPerMonster> GameObjective;


// Time
	
	UPROPERTY()
	float CurrentLeftTime;

	UPROPERTY()
	int32 CurrentMinute = 3;

	UPROPERTY()
	int32 CurrentSecond = 0;

	UPROPERTY()
	FTimerHandle TimeUpdateHandle;

	UFUNCTION()
	void CalcMinute();

	UFUNCTION()
	void GameOver();
	
// Win
	UFUNCTION()
	bool CalculateWin() const;

public:
	bool GetIsCleared() const {return IsCleared;}
	void SetIsCleared(bool InIsCleared) {IsCleared = InIsCleared;}
private:
	UPROPERTY()
	bool IsCleared = false;
	

public:
	int32 GetMinute() const {return CurrentMinute;}
	int32 GetSecond() const {return CurrentSecond;}

	void SetTimerOn();
	void SetTimerOff();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
