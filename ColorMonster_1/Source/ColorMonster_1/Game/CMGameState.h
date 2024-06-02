// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CMSharedDefinition.h"
#include "CMGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnScoreChanged, const FText&, Monster, const FText&, Color, const FText&, Number);

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

private:
	UFUNCTION()
	void UpdateScoreData(const FGameplayTag& Category, const FGameplayTag& Color, int32 Number);
	
	UFUNCTION()
	void UpdateAllScoreUI() const;

	UFUNCTION()
	void UpdateScoreUI(const FGameplayTag& Monster) const;
	
	UPROPERTY()
	TMap<FGameplayTag, FInfoPerColor> GameObjective;
};
