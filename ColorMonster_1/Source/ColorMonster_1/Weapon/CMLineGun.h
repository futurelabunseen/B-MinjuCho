// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CMWeapon.h"
#include "GameFramework/Actor.h"
#include "CMLineGun.generated.h"

UCLASS()
class COLORMONSTER_1_API ACMLineGun : public ACMWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACMLineGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetPlayer(class ACMPlayer* const InPlayer) override;
	virtual void Fire() override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ACMProjectileActor> ProjectileClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FVector MuzzleOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ACMPlayer> Player;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCMPlayerAnimInstance> PlayerAnimInstance;
};
