// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CMCharacterWidget.h"
#include "CMHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class COLORMONSTER_1_API UCMHpBarWidget : public UCMCharacterWidget
{
	GENERATED_BODY()

public:
	UCMHpBarWidget(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void NativeConstruct() override;
	
public:
	FORCEINLINE void SetMaxHp(float InMaxHp) {MaxHp = InMaxHp;}
	UFUNCTION()
	void UpdateHpBar(float InCurrentHp);
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> HpProgressBar;
	
	UPROPERTY()
	float MaxHp;
};
