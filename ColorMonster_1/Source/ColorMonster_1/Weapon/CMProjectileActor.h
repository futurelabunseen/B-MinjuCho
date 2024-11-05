// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "GameplayTags.h"
#include "Interface/CMPoolableInterface.h"
#include "CMProjectileActor.generated.h"

UCLASS()
class COLORMONSTER_1_API ACMProjectileActor : public AActor, public ICMPoolableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACMProjectileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// For Projectile Pooling Interface func
	virtual void Reset() override;
	virtual void Hide() override;

	void SetSyncAndMat(class UCMColorSyncComponent* InColorSync);

	void ChangeColorByLast();
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Color")
	TObjectPtr<UCMColorSyncComponent> ColorSync;

	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	TObjectPtr<class USphereComponent> CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "StaticMesh")
	TObjectPtr<class UStaticMeshComponent> StaticMesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovementComponent;

	UFUNCTION()
	void FireInDirection(const FVector& ShootDirection);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	
protected:

	// Decal Effect For Actor
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Effect, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ADecalActor> EffectClass;

public:
	void SetProjectileCurrentColor(const FGameplayTag& InColor) { ProjectileCurrentColor = InColor; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Color, meta = (AllowPrivateAccess = "true"))
	FGameplayTag ProjectileCurrentColor;
	
	UPROPERTY()
	int8 bCanHit = true;
};

