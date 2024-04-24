// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/CMLineGun.h"

#include "Player/CMProjectileActor.h"
#include "Player/CMPlayer.h"
#include "Animation/CMPlayerAnimInstance.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACMLineGun::ACMLineGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Projectile Class
	static ConstructorHelpers::FClassFinder<ACMProjectileActor> ProjectileRef(TEXT("/Game/Blueprint/BP_CMProjectile.BP_CMProjectile_C"));
	if (ProjectileRef.Class)
	{
		ProjectileClass = ProjectileRef.Class;
		if (!ProjectileClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to Casting Projectile class"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to call Projectile class"));
	}
	MuzzleOffset = FVector(200, 0, 0);
}

// Called when the game starts or when spawned
void ACMLineGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACMLineGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACMLineGun::SetPlayer(ACMPlayer* const InPlayer)
{
	SetOwner(InPlayer);
	Player = InPlayer;
	if(Player)
	{
		PlayerAnimInstance = Cast<UCMPlayerAnimInstance> (InPlayer->GetMesh()->GetAnimInstance());
		if (PlayerAnimInstance == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to cast anim instance in SetPlayer"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to call player from linegun"));
	}
}

void ACMLineGun::Fire()
{
	if (PlayerAnimInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to cast anim instance in CMLineGun"));
	}
	else if (ProjectileClass && PlayerAnimInstance->PlayShooting(0) == 1)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		Owner->GetActorEyesViewPoint(CameraLocation, CameraRotation);

		
		UE_LOG(LogTemp, Warning, TEXT("Line Gun Shoot!"));
	}
}

