// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Character/CMCharacter.h"
#include "CMMonster.generated.h"

/**
 * 
 */
UCLASS()
class COLORMONSTER_1_API ACMMonster : public ACMCharacter
{
	GENERATED_BODY()

public:
	ACMMonster();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void Dead() override;
	void ChangeColor(FGameplayTag InColor);
	
// Color Data -> Tag
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Color, meta = (AllowPrivateAccess = "true"))
	FGameplayTag CurrentColor;
};
