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
};
