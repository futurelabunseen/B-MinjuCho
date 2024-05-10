// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/CMColorGun.h"

#include "Weapon/CMProjectileActor.h"
#include "Player/CMPlayer.h"
#include "Animation/CMPlayerAnimInstance.h"
#include "Color/CMColorSponge.h"
#include "Kismet/GameplayStatics.h"
#include "Color/CMGameplayTag.h"
#include "Character/CMMonster.h"

ACMColorGun::ACMColorGun()
{
	// 총 색깔 세팅
	// Static Mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//StaticMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SkeletalMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/Cube1.Cube1'"));
	if (SkeletalMeshRef.Object)
	{
		StaticMesh->SetStaticMesh(SkeletalMeshRef.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ACMColorGun: Failed to Load Static Mesh Ref"));
	}
	StaticMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	StaticMesh->SetMobility(EComponentMobility::Movable);

	//ObjectDynamic = StaticMesh->CreateDynamicMaterialInstance(0, nullptr, FName(TEXT("None")));
	//ObjectDynamic = UMaterialInstanceDynamic::Create(StaticMesh->GetMaterial(0), this);
	//StaticMesh->CreateDynamicMaterialInstance(0, nullptr);
	
	
	CurrentColor = CM_COLOR_BLUE;
	
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
	MaxBullet = CurrentBullet = 3;
}

void ACMColorGun::BeginPlay()
{
	Super::BeginPlay();

	ObjectDynamic = UMaterialInstanceDynamic::Create(StaticMesh->GetMaterial(0), this);
	StaticMesh->SetMaterial(0, ObjectDynamic);
	
	ChangeColor(CurrentColor);
	CurrentColor = CM_COLOR_GREEN;
	ChangeColor(CurrentColor);
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
	if(CurrentBullet <= 0)
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
				Projectile->SetCurrentColor(CurrentColor);
				Projectile->FireInDirection(LaunchDirection);
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("Color Gun Shoot!"));
		--CurrentBullet;
	}
}

void ACMColorGun::Reload()
{
	CurrentBullet = MaxBullet;
	if (PlayerAnimInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to cast anim instance in ACMColorGun::Reload"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ColorGun Reload"));
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
		
		UE_LOG(LogTemp, Warning, TEXT("Line Trace Shoot!"));
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.0f, 0,0);
		if(bResult && FireHit.GetActor())
		{
			ACMColorSponge* Sponge = Cast<ACMColorSponge>(FireHit.GetActor());
			
			if(Sponge)
			{
				UE_LOG(LogTemp, Warning, TEXT("GetCurrentColor in ShootTrace: %s"), *(Sponge->GetCurrentColor().ToString()));
				Absorb(Sponge->GetCurrentColor());
			}
		}
	}
}

void ACMColorGun::Absorb(const FGameplayTag& SpongeColor)
{
	CurrentColor = SpongeColor;
	UE_LOG(LogTemp, Warning, TEXT("Absorb in CMColorGun: %s"), *(CurrentColor.ToString()));
	ChangeColor(CurrentColor);
}

void ACMColorGun::ChangeColor(const FGameplayTag& InColor)
{
	//UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), ObjectDynamic));
	
	// UMaterialInstanceDynamic* MaterialInstance = Cast<UMaterialInstanceDynamic>(StaticMesh->GetMaterial(0));
	// if(MaterialInstance)
	// {
	// 	MaterialInstance->SetVectorParameterValue(TEXT("Color"), ACMMonster::TranslateColor(InColor));
	// 	UE_LOG(LogTemp, Warning, TEXT("ChangeColor in CMColorGun: %s"), *(InColor.GetTagName().ToString()));
	// }

	// ObjectDynamic = UMaterialInstanceDynamic::Create(StaticMesh->GetMaterial(0), this);
	// StaticMesh->SetMaterial(0, ObjectDynamic);
	if(ObjectDynamic)
	{
		ObjectDynamic->SetVectorParameterValue(FName("Tint"), ACMMonster::TranslateColor(InColor));
		UE_LOG(LogTemp, Warning, TEXT("ChangeColor in CMColorGun: %s"), *(ACMMonster::TranslateColor(InColor).ToString()));
		UE_LOG(LogTemp, Warning, TEXT("ObjectDynamic in CMColorGun: %s"), *ObjectDynamic->GetName());
		//StaticMesh->SetMaterial(0, ObjectDynamic);
		
	}
}








