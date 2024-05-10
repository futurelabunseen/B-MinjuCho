// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/CMLineGun.h"

#include "Player/CMPlayer.h"
#include "Animation/CMPlayerAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"

// Sets default values
ACMLineGun::ACMLineGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Bullet Num
	MaxBullet = CurrentBullet = 5;
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
	// Skip if it has no bullet
	if(CurrentBullet <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("BULLET IS NOT ENOUGH!! ACMLineGun::Fire"));
		return;
	}
	// Skip if it has no Animation
	if (PlayerAnimInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to cast anim instance in ACMLineGun"));
	}
	// 오른손 슈팅 Animation 정상 처리 됐을 때
	else if (PlayerAnimInstance->PlayShooting(0) == 1)
	{
		ShootTrace();
		--CurrentBullet;
	}
}

void ACMLineGun::Reload()
{
	// Skip if it has enough bullet
	if(CurrentBullet == MaxBullet)
	{
		UE_LOG(LogTemp, Warning, TEXT("Bullet is Already Full - ACMLineGun::Reload"));
		return;
	}
	CurrentBullet = MaxBullet;
}

void ACMLineGun::ShootTrace()
{
	FHitResult FireHit;

	FVector2D ViewportSize;
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}

	FVector2D CrosshairLocation(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);
	FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection;
	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(
		UGameplayStatics::GetPlayerController(this, 0),
		CrosshairLocation,
		CrosshairWorldPosition,
		CrosshairWorldDirection
	);

	if (bScreenToWorld)
	{
		FVector Start = CrosshairWorldPosition;
		FVector End = Start + CrosshairWorldDirection * 80000.0f;

		bool bResult = GetWorld()->LineTraceSingleByChannel(
			FireHit,
			Start,
			End,
			ECollisionChannel::ECC_Visibility
		);
		
		UE_LOG(LogTemp, Warning, TEXT("Line Trace Shoot!"));
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.0f, 0,0);
		if(bResult && FireHit.GetActor())
		{
			TraceHit(FireHit);
		}
	}
}

void ACMLineGun::TraceHit(const FHitResult& FireHit)
{
	FDamageEvent DamageEvent;
	FireHit.GetActor()->TakeDamage(40.0f, DamageEvent, Player->GetController(), this);
}

