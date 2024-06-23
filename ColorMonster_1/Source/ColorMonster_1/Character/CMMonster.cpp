// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CMMonster.h"

#include "AI/CMAIController.h"
#include "Animation/CMPlayerAnimInstance.h"
#include "CMSharedDefinition.h"
#include "Components/CapsuleComponent.h"
#include "Character/CMMonsterAnimInstance.h"
#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"
#include "Game/CMGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/CMPlayer.h"
#include "UI/CMWidgetComponent.h"

ACMMonster::ACMMonster()
{
	PrimaryActorTick.bCanEverTick = true;
	// Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/sk_CharM_Base.sk_CharM_Base'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}
	GetMesh()->SetCollisionProfileName(TEXT("Enemy"));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	// Animation
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/Animation/AnimBP_CMMonster.AnimBP_CMMonster_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to call anim instance class From Monster"));
	}
	AnimInstance = Cast<UCMMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	
	// Collision
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	// Default Color
	CurrentColor = CM_COLOR_NONE;
	CurrentCategory = CM_MONSTER_BASE;
	// AI Controller 속성
	AIControllerClass = ACMAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// Load Decal Material
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> DecalMaterialRef(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Vefects/Blood_VFX/VFX/Decals/MI_VFX_Blood_Decal_WallSplatter01_Censor.MI_VFX_Blood_Decal_WallSplatter01_Censor'"));
	if (DecalMaterialRef.Object)
	{
		DecalMaterial = DecalMaterialRef.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to call DecalMetrial Object"));
	}
	DecalSize = FVector(32.0f, 48.0f, 80.0f);

	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));
	ensure(DecalComponent);
	DecalComponent->SetupAttachment(RootComponent);
	InitializeDecalComponent();

	// Big Size of Monster Collision against Monster
	MonsterCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MonsterCollisionComponent"));
	MonsterCollisionComponent->SetCollisionProfileName(TEXT("ConfrontMonster"));
	MonsterCollisionComponent->SetWorldScale3D(FVector(3.0f, 3.0f, 3.0f));
}

void ACMMonster::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = Cast<UCMMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	if(AnimInstance)
	{
		AnimInstance->SetMonster(this);
	}
	
	// 모든 매터리얼 다루기 위한 Dynamic 세팅
	for(int i=0; i<GetMesh()->GetNumMaterials();++i)
	{
		GetMesh()->CreateAndSetMaterialInstanceDynamic(i);
	}
	ChangeColor(CurrentColor);

	// Load Player
	LoadPlayer();
}

void ACMMonster::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	RotateHPBarToCamera();
}

void ACMMonster::RotateHPBarToCamera()
{
	if (PlayerController)
	{
		// 카메라 위치와 몬스터 위치에 따라 Rotate 하는 방법
		//FVector CameraLocation = PlayerController->PlayerCameraManager->GetCameraLocation();
		//FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CameraLocation);
		//HpBar->SetWorldRotation(LookAtRotation);
		// 그냥 카메라 Rotation 따르는 방법
		FRotator CameraRotation = PlayerController->PlayerCameraManager->GetCameraRotation() + FRotator(0,180.0f, 0);
		HpBar->SetWorldRotation(CameraRotation);
	}
	else
	{
		LoadPlayer();
	}
}

void ACMMonster::Dead()
{
	Super::Dead();
	if(!AnimInstance)
	{
		AnimInstance = Cast<UCMMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	}
	ensure(AnimInstance);
	if(AnimInstance)
	{
		AnimInstance->PlayDeadMontage();
		ACMGameState* GameState = GetWorld()->GetGameState<ACMGameState>();
		if(GameState)
		{
			GameState->UpdateFromDead(CurrentCategory, CurrentColor);
		}
	}
}

void ACMMonster::Attack()
{
	Super::Attack();

	if(!AnimInstance)
	{
		AnimInstance = Cast<UCMMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	}
	ensure(AnimInstance);
	if(AnimInstance)
	{
		AnimInstance->PlayAttackMontage();
	}
}

float ACMMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float InDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if(!AnimInstance)
	{
		AnimInstance = Cast<UCMMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	}
	ensure(AnimInstance);
	if(AnimInstance)
	{
		AnimInstance->PlayDamageMontage();
	}
	return InDamage;
}

void ACMMonster::LoadPlayer()
{
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if(PlayerController)
	{
		
	}
}

void ACMMonster::InitializeDecalComponent() const
{
	// Initialize Shape
	DecalComponent->SetDecalMaterial(DecalMaterial);
	DecalComponent->DecalSize = DecalSize;

	// Initialize Visibility & Receive State
	DecalComponent->SetVisibility(false);
	TurnReceiveDecal(false);

	// Position
	// DecalComponent->SetWorldLocation(HitMonster->GetActorLocation());
	// DecalComponent->SetWorldRotation(HitMonster->GetActorRotation());
}

void ACMMonster::TurnReceiveDecal(bool IsTurnOn) const
{
	GetMesh()->SetReceivesDecals(IsTurnOn);
}

void ACMMonster::UpdateDecal(const FLinearColor& InDecalColor) const
{
	if(DecalComponent)
	{
		DecalComponent->SetVisibility(true);
		TurnReceiveDecal(true);
		
		// Set the color of the Decal Material
		UMaterialInstanceDynamic* DecalDynamicMaterial = DecalComponent->CreateDynamicMaterialInstance();
		if (DecalDynamicMaterial)
		{
			DecalDynamicMaterial->SetVectorParameterValue(FName("Tint"), InDecalColor);
		}
	}
}

void ACMMonster::UpdateDecal(const FLinearColor& InDecalColor, const FVector& InDecalSize) const
{
	if(DecalComponent)
	{
		UpdateDecal(InDecalColor);
		DecalComponent->DecalSize = InDecalSize;
	}
}

void ACMMonster::ChangeColor(const FGameplayTag& InColor)
{
	CurrentColor = InColor;
	const FLinearColor RealColor = CMSharedDefinition::TranslateColor(CurrentColor);
	for(int i=0; i<GetMesh()->GetNumMaterials(); ++i)
	{
		// 각 매터리얼에 설정된 Dynamic 가져오기
		UMaterialInterface* SkeletalMeshMaterial = GetMesh()->GetMaterial(i);
		UMaterialInstanceDynamic* DynamicMaterial = 
			Cast<UMaterialInstanceDynamic>(SkeletalMeshMaterial);
		if(DynamicMaterial)
		{
			// 전체 Parameter 훑는 방법
			// TArray<FMaterialParameterInfo> MaterialParameters;
			// TArray<FGuid> Guid;
			// Dynamic->GetAllVectorParameterInfo(MaterialParameters, Guid);
			// for(FMaterialParameterInfo MaterialParam : MaterialParameters)
			// {
			// 	Dynamic->SetVectorParameterValueByInfo(MaterialParam, RealColor);
			// }
			// 현재 컬러로 곱하기
			DynamicMaterial->SetVectorParameterValue(FName("Tint"), RealColor);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ACMMonster::Failed to Load DynmaicMaterial"));
		}
	}
}

void ACMMonster::AfterAnimEndedAttack()
{
	OnAttackFinished.ExecuteIfBound();
	if(HitPlayer)
	{
		FDamageEvent DamageEvent;
		HitPlayer->TakeDamage(GetAttackDamage(), DamageEvent, GetController(), this);
	}
}

void ACMMonster::TraceHit()
{
	FHitResult OutHitResult;
	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + GetActorForwardVector() * GetAttackRange();
	
	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel4, FCollisionShape::MakeSphere(GetAttackRadius()));
	
	if (HitDetected)
	{
		HitPlayer = Cast<ACMPlayer>(OutHitResult.GetActor());
	}
#if ENABLE_DRAW_DEBUG

	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
	float CapsuleHalfHeight = AttackRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);

#endif
}


float ACMMonster::GetAIPatrolRadius()
{
	return 800.0f;
}

float ACMMonster::GetAIDetectRange()
{
	return 400.0f;
}

float ACMMonster::GetAIAttackRange()
{
	return AttackRange + AttackRadius * 2;
}

float ACMMonster::GetAITurnSpeed()
{
	return 2.0f;
}

void ACMMonster::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void ACMMonster::AttackByAI()
{
	// Attack 함수 실행
	Attack();
	//UE_LOG(LogTemp, Warning, TEXT("Monster Attack By AI!"));
}

// // CharacterBase 클래스에서 새로 생성한 가상함수 override (공격이 끝날 때 호출될 예정)
// // AnimNotify 함수라서 자동 호출됨
// void ACMMonster::NotifyComboActionEnd()
// {
// 	Super::NotifyComboActionEnd(); // 아무것도 없음
// 	OnAttackFinished.ExecuteIfBound(); // 델리게이트 바인딩 됐다면, 함수 호출
// }

