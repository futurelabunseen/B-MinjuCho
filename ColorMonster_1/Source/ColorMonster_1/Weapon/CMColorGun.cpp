// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/CMColorGun.h"

#include "Weapon/CMProjectileActor.h"
#include "Player/CMPlayer.h"
#include "Animation/CMPlayerAnimInstance.h"
#include "Color/CMColorSponge.h"
#include "Kismet/GameplayStatics.h"
#include "CMSharedDefinition.h"
#include "Character/CMMonster.h"
#include "Math/RandomStream.h"
#include "Weapon/CMColorSyncComponent.h"

ACMColorGun::ACMColorGun()
{
	// 총 색깔 세팅
	// Skeletal Mesh
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Sci-Fi_Assault_Rifle/Assault_Rifle/SK_Rifle_Mesh/SK_Butt.SK_Butt'"));
	if (SkeletalMeshRef.Object)
	{
		SkeletalMesh->SetSkeletalMesh(SkeletalMeshRef.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ACMColorGun: Failed to Load Static Mesh Ref"));
	}

	SkeletalMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	SkeletalMesh->SetMobility(EComponentMobility::Movable);

	// Color Component
	ColorSync = CreateDefaultSubobject<UCMColorSyncComponent>(TEXT("ColorSync"));

	
	// 투사체 세팅
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

	// Bullet Num
	SetMaxBullet(3);
	SetCurrentBullet(0);
}

void ACMColorGun::BeginPlay()
{
	Super::BeginPlay();

	if (ColorSync)
	{
		// Set Mat by Created Sync Dynamic Mat
		ColorSync->CreateDynamicMaterial(SkeletalMesh->CreateAndSetMaterialInstanceDynamic(0));
		SkeletalMesh->SetMaterial(0, ColorSync->GetDynamicInstance());
		// Set As Default Color
		CallChangeColor(ColorSync->GetCurrentColor());
	}
}

void ACMColorGun::SetPlayer(ACMPlayer* const InPlayer)
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
		UE_LOG(LogTemp, Warning, TEXT("Failed to call player from ACMColorGun"));
	}
}

void ACMColorGun::Fire()
{
	// Skip if it has no bullet
	if(GetCurrentBullet() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("BULLET IS NOT ENOUGH!! ACMColorGun::Fire"));
		return;
	}
	// Skip if it has no Animation
	if (PlayerAnimInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to cast anim instance in ACMColorGun::Fire"));
	}
	// 왼손 슈팅 Animation 정상 처리 됐을 때 총알 쏘기
	else if (ProjectileClass && PlayerAnimInstance->PlayShooting(1) == 1)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		Owner->GetActorEyesViewPoint(CameraLocation, CameraRotation);

		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 10.0f;
		if (GetWorld())
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			ACMProjectileActor* Projectile = GetWorld()->SpawnActor<ACMProjectileActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				FVector LaunchDirection = MuzzleRotation.Vector();

				// Update Bullet Num
				SetCurrentBullet(GetCurrentBullet() - 1);

				if (ColorSync)
				{
					// Memorizing Color in Each Projectile
					Projectile->SetProjectileCurrentColor(ColorSync->GetCurrentColor());

					// If it is not the Last, Set DynMat As Shared by ColorGun
					if (GetCurrentBullet() != 0)
					{
						Projectile->SetSyncAndMat(ColorSync);
					}
					else
					{
						// Last Projectile has to be Localized DynMat
						Projectile->ChangeColorByLast();
					}
				}
				Projectile->FireInDirection(LaunchDirection);
			}
		}
		// Update Bullet UI
		OnBulletChanged.Broadcast(GetCurrentBullet(), GetMaxBullet());
	}
	if(GetCurrentBullet() == 0)
	{
		CallChangeColor(CM_COLOR_NONE);
	}
}

void ACMColorGun::Reload()
{
	if (PlayerAnimInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to cast anim instance in ACMColorGun::Reload"));
	}
	else
	{
		ShootTrace();
	}
}

void ACMColorGun::ShootTrace() 
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
		
		//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.0f, 0,0);
		if(bResult && FireHit.GetActor())
		{
			ACMColorSponge* Sponge = Cast<ACMColorSponge>(FireHit.GetActor());
			
			if(Sponge)
			{
				CallChangeColor(Sponge->GetCurrentColor());
			}
		}
	}
}

void ACMColorGun::CallChangeColor(const FGameplayTag& InColor)
{
	if(ColorSync)
	{
		ColorSync->ChangeColor(InColor);
		OnColorChanged.Broadcast(InColor);
		// 색이 제대로 바뀌었을 때만 장전 완료 처리
		if(InColor != CM_COLOR_NONE)
		{
			// Update Bullet
			SetCurrentBullet(GetMaxBullet());
			OnBulletChanged.Broadcast(GetCurrentBullet(), GetMaxBullet());
			
			UE_LOG(LogTemp, Warning, TEXT("ColorGun Reload : %s"), *InColor.ToString());
		}
	}
}
