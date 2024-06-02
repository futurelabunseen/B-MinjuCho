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

private:
	UPROPERTY()
	FGameplayTag CurrentCategory;

// Basic Action
protected:
	virtual void BeginPlay() override;
	virtual void Dead() override;
	virtual void Attack() override;
public:
	FORCEINLINE float GetAttackRange() const {return AttackRange;}
	FORCEINLINE float GetAttackRadius() const {return AttackRadius;}
	FORCEINLINE float GetAttackDamage() const {return AttackDamage;}
// Attack Data
private:
	float AttackRange = 100.0f;
	float AttackRadius = 100.0f;
	float AttackDamage = 10.0f;
	
// Color Data -> Tag
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Color, meta = (AllowPrivateAccess = "true"))
	FGameplayTag CurrentColor;

	UFUNCTION()
	void ChangeColor(const FGameplayTag& InColor);

private:
	UPROPERTY();
	TArray<TObjectPtr<UMaterialInstanceDynamic>> MaterialArray;

	// AnimInstance
	UPROPERTY()
	TObjectPtr<class UCMMonsterAnimInstance> AnimInstance;
	
public:
	UFUNCTION()
	void AfterAnimEndedAttack();

	void TraceHit();
private:
	TObjectPtr<class ACMPlayer> HitPlayer;

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
