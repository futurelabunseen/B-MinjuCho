// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "GameplayTagContainer.h"
#include "CMColorDecalEffect.generated.h"

/**
 * 
 */
UCLASS()
class COLORMONSTER_1_API ACMColorDecalEffect : public ADecalActor
{
	GENERATED_BODY()

public:
	ACMColorDecalEffect();

	virtual void BeginPlay() override;

	UFUNCTION()
	void ChangeColor(const FGameplayTag& InColor);

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Color, meta = (AllowPrivateAccess = "true"))
	FGameplayTag CurrentColor;

// Timer
public:
	void SetTimerOn();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Time)
	int32 DestroyTime;
	
protected:
	UFUNCTION()
	void CalcMinute();
private:
	UPROPERTY()
	FTimerHandle DecalTimerHandle;
	
	int32 BeforeDestroyTime = 0;

	void StopTimer();
};
