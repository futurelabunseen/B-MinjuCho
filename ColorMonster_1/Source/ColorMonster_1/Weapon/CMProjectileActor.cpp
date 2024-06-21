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
	// static ConstructorHelpers::FObjectFinder<UMaterial> MaterialRef(TEXT(""));
	// if (MaterialRef.Object)
	// {
	// 	StaticMesh->SetMaterial(0, MaterialRef.Object);
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("CMPROJECTILEACTOR: Failed to Load Material"));
	// }

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
	/*static ConstructorHelpers::FClassFinder<ADecalActor> EffectClassRef(TEXT("/Game/Blueprint/BP_CMDecalEffect.BP_CMDecalEffect_C"));
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
	}*/

	// 2. For Decal Component
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> DecalMaterialRef(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Vefects/Blood_VFX/VFX/Decals/MI_VFX_Blood_Decal_WallSplatter01_Censor.MI_VFX_Blood_Decal_WallSplatter01_Censor'"));
	if (DecalMaterialRef.Object)
	{
		DecalMaterial = DecalMaterialRef.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to call DecalMetrial Object"));
	}
	DecalSize = FVector(32.0f, 64.0f, 64.0f);
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
	//CurrentColor = InColor;
}

void ACMProjectileActor::AttachDecalToMonster(AActor* HitMonster, const FLinearColor& InColor)
{
	//UDecalComponent* DecalComponent = UGameplayStatics::SpawnDecalAttached(DecalMaterial, DecalSize,
	//	HitMonster->GetRootComponent(), // Attach Component
	//	NAME_None,						// Socket Name
	//	HitMonster->GetActorLocation(), HitMonster->GetActorRotation(), // Relative Pos, Rot 
	//	EAttachLocation::KeepRelativeOffset, // Attach Type
	//	10.0f);							// Decal LifeTime (sec) [0: Permanent]
	UDecalComponent* DecalComponent = NewObject<UDecalComponent>(HitMonster);
	if (DecalComponent)
	{
		// Initialize
		DecalComponent->SetDecalMaterial(DecalMaterial);
		DecalComponent->DecalSize = DecalSize;

		// Change Color
		UMaterialInstanceDynamic* DynamicMaterial =
			DecalComponent->CreateDynamicMaterialInstance();
		if (DynamicMaterial)
		{
			// Multiply by CurrentColor
			DynamicMaterial->SetVectorParameterValue(FName("Tint"), InColor);
		}

		// Pin Position to Monster
		DecalComponent->SetupAttachment(HitMonster->GetRootComponent());
		DecalComponent->RegisterComponent();

		// Position
		DecalComponent->SetWorldLocation(HitMonster->GetActorLocation());
		DecalComponent->SetWorldRotation(HitMonster->GetActorRotation());

	}

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
			// refer interface from ideugu class

			// 1. Decal Actor
			/*ACMColorDecalEffect* DecalEffect = GetWorld()->SpawnActor<ACMColorDecalEffect>(EffectClass);
			if (DecalEffect)
			{
				DecalEffect->ChangeColor(CurrentColor);
				DecalEffect->SetActorLocation(HitMonster->GetActorLocation());

			}*/

			// 2. Decal Component
			AttachDecalToMonster(HitMonster, CMSharedDefinition::TranslateColor(CurrentColor));

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