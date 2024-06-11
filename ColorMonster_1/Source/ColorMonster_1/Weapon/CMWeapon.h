// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMWeapon.generated.h"

UCLASS()
class COLORMONSTER_1_API ACMWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACMWeapon();
	
public:
	virtual void SetPlayer(class ACMPlayer* const InPlayer);
	
	virtual void Fire();
	virtual void Reload();

	int32 GetMaxBullet() const {return MaxBullet;}
	int32 GetCurrentBullet() const {return CurrentBullet;}
	void SetMaxBullet(int32 InMaxNum) {MaxBullet = InMaxNum;}
	void SetCurrentBullet(int32 InCurrentNum) {CurrentBullet = InCurrentNum;}
	
private:
	UPROPERTY(EditAnywhere, Category=Bullet)
	int32 MaxBullet;
	UPROPERTY(EditAnywhere, Category=Bullet)
	int32 CurrentBullet;
};
