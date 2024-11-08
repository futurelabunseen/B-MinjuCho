// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CMWeapon.h"
#include "GameFramework/Actor.h"
#include "CMLineGun.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRightBulletChanged, int32, CurrentNum, int32, MaxNum);

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
	virtual void Reload() override;
	void ShootTrace();
	void TraceHit(const FHitResult& FireHit);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ACMPlayer> Player;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCMPlayerAnimInstance> PlayerAnimInstance;

public:
	// Delgate Instance
	FOnRightBulletChanged OnBulletChanged;
};
