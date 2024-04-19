// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CMPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class COLORMONSTER_1_API UCMPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	UCMPlayerAnimInstance();


protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class ACMPlayer> Owner;

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Fire, Meta = (AllowPrivateAccess = true))
	TObjectPtr<class UAnimMontage> RightFireMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Fire, Meta = (AllowPrivateAccess = true))
	TObjectPtr<class UAnimMontage> LeftFireMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Fire, Meta = (AllowPrivateAccess = true))
	TObjectPtr<class UAnimMontage> RightLeftMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Fire, Meta = (AllowPrivateAccess = true))
	TObjectPtr<class UAnimMontage> LeftRightMontage;


public:
	UFUNCTION()
	void PlayShooting();

	UFUNCTION()
	void PlayConverting();
};
