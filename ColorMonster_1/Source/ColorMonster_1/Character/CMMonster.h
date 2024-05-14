// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Character/CMCharacter.h"
#include "Components/PrimitiveComponent.h"
#include "Interface/CMAIInterface.h"
#include "CMMonster.generated.h"

/**
 * 
 */
UCLASS()
class COLORMONSTER_1_API ACMMonster : public ACMCharacter, public ICMAIInterface
{
	GENERATED_BODY()

public:
	ACMMonster();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;
	virtual void Dead() override;
	
// Color Data -> Tag
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Color, meta = (AllowPrivateAccess = "true"))
	FGameplayTag CurrentColor;

	UFUNCTION()
	void ChangeColor(const FGameplayTag& InColor);

	static const FLinearColor& TranslateColor(const FGameplayTag& ColorTag);

private:
	UPROPERTY();
	TArray<TObjectPtr<UMaterialInstanceDynamic>> MaterialArray;

// AI Interface
protected:
	FAICharacterAttackFinished OnAttackFinished;
	
	virtual float GetAIPatrolRadius();
	virtual float GetAIDetectRange();
	virtual float GetAIAttackRange();
	virtual float GetAITurnSpeed();

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished);
	virtual void AttackByAI();
};
