// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/CMProjectileActor.h"

#include "Character/CMMonster.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CMSharedDefinition.h"
#include "Weapon/CMColorDecalEffect.h"
#include "Components/DecalComponent.h"

// Sets default values
ACMProjectileActor::ACMProjectileActor()
{
	// Sphere Collision
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	CollisionComponent->InitSphereRadius(16.0f);
	RootComponent = CollisionComponent;

	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &ACMProjectileActor::OnHit);
	//CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACMProjectileActor::OnTriggerBegin);

	// Players can't walk on it
	CollisionComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComponent->CanCharacterStepUpOn = ECB_No;

	// Static Mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(CollisionComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/FPWeapon/Mesh/FirstPersonProjectileMesh.FirstPersonProjectileMesh'"));
	if (StaticMeshRef.Object)
	{
		StaticMesh->SetStaticMesh(StaticMeshRef.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CMPROJECTILEACTOR: Failed to Load Static Mesh"));
	}
	
	// Movement
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = false;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.6f;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

	CurrentColor = CM_COLOR_NONE;

	// 1. For Decal Actor
	// Load Effect
	static ConstructorHelpers::FClassFinder<ADecalActor> EffectClassRef(TEXT("/Game/Blueprint/BP_CMDecalEffect.BP_CMDecalEffect_C"));
	if (EffectClassRef.Class)
	{
		EffectClass = EffectClassRef.Class;
		if (EffectClass == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to Casting Effect class"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to call Effect class"));
	}

}

// Called when the game starts or when spawned
void ACMProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
	// Dynamic 세팅
	StaticMesh->CreateAndSetMaterialInstanceDynamic(0);
}

// Called every frame
void ACMProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACMProjectileActor::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void ACMProjectileActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != this) && (OtherComponent != nullptr))
	{
		// Knock Back
		//OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);

		ensure(OtherActor != nullptr);
		ACMMonster* HitMonster = Cast<ACMMonster>(OtherActor);
		if (HitMonster != nullptr)
		{
			HitMonster->ChangeColor(CurrentColor);

			// 1. Decal Actor
			ACMColorDecalEffect* DecalEffect = GetWorld()->SpawnActor<ACMColorDecalEffect>(EffectClass);
			if (DecalEffect)
			{
				DecalEffect->ChangeColor(CurrentColor);
				DecalEffect->SetActorLocation(HitMonster->GetActorLocation() + FVector(0.0f, 0.0f, -142.792745));
				DecalEffect->SetTimerOn();
			
			}

			// 2. Decal Component
			HitMonster->UpdateDecal(CMSharedDefinition::TranslateColor(CurrentColor));

		}

		Destroy();
	}
}
//GetWorld()->OverlapMultiByChannel()
//UKismetSystemLibrary::SphereOverlapActors()
//UKismetSystemLibrary::SphereTraceSingle()

void ACMProjectileActor::ChangeColor(const FGameplayTag& InColor)
{
	CurrentColor = InColor;
	const FLinearColor RealColor = CMSharedDefinition::TranslateColor(CurrentColor);
	for (int i = 0; i < StaticMesh->GetNumMaterials(); ++i)
	{
		// 각 매터리얼에 설정된 Dynamic 가져오기
		UMaterialInterface* SkeletalMeshMaterial = StaticMesh->GetMaterial(i);
		UMaterialInstanceDynamic* DynamicMaterial =
			Cast<UMaterialInstanceDynamic>(SkeletalMeshMaterial);
		if (DynamicMaterial)
		{
			// 현재 컬러로 곱하기
			DynamicMaterial->SetVectorParameterValue(FName("Tint"), RealColor);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ACMProjectileActor::Failed to Load DynmaicMaterial"));
		}
	}
}