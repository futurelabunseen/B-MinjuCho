// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/CMWeapon.h"
#include "GameplayTagContainer.h"
#include "CMColorGun.generated.h"

/**
 * 
 */
UCLASS()
class COLORMONSTER_1_API ACMColorGun : public ACMWeapon
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ACMColorGun();


	virtual void SetPlayer(class ACMPlayer* const InPlayer) override;
	virtual void Fire() override;
	virtual void Reload() override;
	void ShootTrace();
	void Absorb(const FGameplayTag& SpongeColor);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ACMProjectileActor> ProjectileClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FVector MuzzleOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ACMPlayer> Player;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCMPlayerAnimInstance> PlayerAnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Color, meta = (AllowPrivateAccess = "true"))
	FGameplayTag CurrentColor;
};
