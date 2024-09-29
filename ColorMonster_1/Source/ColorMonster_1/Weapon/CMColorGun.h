// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/CMWeapon.h"
#include "GameplayTagContainer.h"
#include "CMColorGun.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnColorChanged, const FGameplayTag&, InColor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBulletChanged, int32, CurrentNum, int32, MaxNum);
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

protected:
	virtual void BeginPlay() override;
public:
	virtual void SetPlayer(class ACMPlayer* const InPlayer) override;
	virtual void Fire() override;
	virtual void Reload() override;
	void ShootTrace();
	void CallChangeColor(const FGameplayTag& InColor);
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ACMProjectileActor> ProjectileClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	FVector MuzzleOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ACMPlayer> Player;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCMPlayerAnimInstance> PlayerAnimInstance;

	UPROPERTY(VisibleDefaultsOnly, Category = "Color")
	TObjectPtr<class UCMColorSyncComponent> ColorSync;

private:
	UPROPERTY(EditAnywhere, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> SkeletalMesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMaterialInstanceDynamic> ObjectDynamic;

	// Delgate Instance
public:
	FOnColorChanged OnColorChanged;
	FOnBulletChanged OnBulletChanged;
};
