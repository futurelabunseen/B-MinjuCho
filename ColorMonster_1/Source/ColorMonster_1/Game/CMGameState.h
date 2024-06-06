// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CMSharedDefinition.h"
#include "CMGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnScoreChanged, const FText&, Monster, const FText&, Color, const FText&, Number);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTimeChanged, int32, Minute, int32, Second);

/**
 * 
 */
UCLASS()
class COLORMONSTER_1_API ACMGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ACMGameState();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void UpdateFromDead(const FGameplayTag& Category, const FGameplayTag& Color);
	
	// Delagate Instance
	FOnScoreChanged OnScoreChanged;
	FOnTimeChanged OnTimeChanged;

	float GetCurrentLeftTime() const { return CurrentLeftTime; }
	void SetCurrentLeftTime(float InTime) { CurrentLeftTime = InTime; }

private:
	UFUNCTION()
	void UpdateScoreData(const FGameplayTag& Category, const FGameplayTag& Color, int32 Number);
	
	UFUNCTION()
	void UpdateAllScoreUI() const;

	UFUNCTION()
	void UpdateScoreUI(const FGameplayTag& Monster) const;
	
	UPROPERTY()
	TMap<FGameplayTag, FInfoPerColor> GameObjective;

	UPROPERTY()
	int32 Level;

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

public:
	int32 GetMinute() const {return CurrentMinute;}
	int32 GetSecond() const {return CurrentSecond;}

	void SetTimerOn();
};
