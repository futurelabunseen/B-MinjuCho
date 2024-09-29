// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/CMProjectileActor.h"

#include "Character/CMMonster.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CMSharedDefinition.h"
#include "Weapon/CMColorDecalEffect.h"
#include "Components/DecalComponent.h"
#include "Weapon/CMColorSyncComponent.h"

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
}

// Called every frame
void ACMProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACMProjectileActor::SetSyncAndMat(UCMColorSyncComponent* InColorSync)
{
	ColorSync = InColorSync;
	if (ColorSync && ColorSync->GetDynamicInstance())
	{
		// Set Mat by Sync Dynamic Mat
		StaticMesh->SetMaterial(0, ColorSync->GetDynamicInstance());
	}
}

void ACMProjectileActor::ChangeColorByLast()
{
	UMaterialInstanceDynamic* TempDynamic = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (TempDynamic)
	{
		const FLinearColor RealColor = CMSharedDefinition::TranslateColor(ProjectileCurrentColor);
		TempDynamic->SetVectorParameterValue(FName("Tint"), RealColor);
		StaticMesh->SetMaterial(0, TempDynamic);

		UE_LOG(LogTemp, Warning, TEXT("ACMProjectileActor::ChangeColorByLast"));
	}
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
			HitMonster->ChangeColor(ProjectileCurrentColor);

			// 1. Decal Actor
			ACMColorDecalEffect* DecalEffect = GetWorld()->SpawnActor<ACMColorDecalEffect>(EffectClass);
			if (DecalEffect)
			{
				DecalEffect->ChangeColor(ProjectileCurrentColor);
				DecalEffect->SetActorLocation(HitMonster->GetActorLocation() + FVector(0.0f, 0.0f, -142.792745));
				
			
			}

			// 2. Decal Component
			HitMonster->UpdateDecal(CMSharedDefinition::TranslateColor(ProjectileCurrentColor));

		}

		Destroy();
	}
}
//GetWorld()->OverlapMultiByChannel()
//UKismetSystemLibrary::SphereOverlapActors()
//UKismetSystemLibrary::SphereTraceSingle()
