// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/CMCharacterWidgetInterface.h"
#include "CMCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHpChanged, float, CurrentHP);

UCLASS()
class COLORMONSTER_1_API ACMCharacter : public ACharacter, public ICMCharacterWidgetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACMCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// HP
protected:
	UPROPERTY()
	float CurrentHP;
	UPROPERTY()
	float MaxHP;
	FORCEINLINE float GetCurrentHP() const { return CurrentHP; }
	FORCEINLINE void SetCurrentHP(float InValue) { CurrentHP = InValue; }
	FORCEINLINE float GetMaxHP() const { return MaxHP; }
	FORCEINLINE void SetMaxHP(float InValue) { MaxHP = InValue; }
	// UI Widget Section
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCMWidgetComponent> HpBar;
	virtual void SetupCharacterWidget(class UCMCharacterWidget* InCharacterWidget) override;

public:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	                         AActor* DamageCauser) override;
	virtual void UpdateHPFromDamage(float Damage);
	virtual void Dead();
	virtual void Attack();

	FOnHpChanged OnHpChanged;
};
