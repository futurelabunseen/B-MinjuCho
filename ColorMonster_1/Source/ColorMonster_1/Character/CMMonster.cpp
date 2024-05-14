// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CMMonster.h"

#include "AI/CMAIController.h"
#include "Animation/CMPlayerAnimInstance.h"
#include "Color/CMGameplayTag.h"
#include "Components/CapsuleComponent.h"

ACMMonster::ACMMonster()
{
	// Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonTwinblast/Characters/Heroes/TwinBlast/Meshes/TwinBlast.TwinBlast'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}
	GetMesh()->SetCollisionProfileName(TEXT("Enemy"));

	// Animation
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/ParagonTwinblast/Characters/Heroes/TwinBlast/Twinblast_AnimBlueprint.Twinblast_AnimBlueprint_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to call anim instance class From Monster"));
	}
	// Collision
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	// Default Color
	CurrentColor = CM_COLOR_NONE;
	// 모든 매터리얼 다루기 위한 Dynamic 세팅
	for(int i=0; i<GetMesh()->GetNumMaterials();++i)
	{
		GetMesh()->CreateDynamicMaterialInstance(i, nullptr);
	}

	// AI Controller 속성
	AIControllerClass = ACMAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

float ACMMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogTemp, Warning, TEXT("Actor: %s took Damage : %f"), *GetName(), FinalDamage);
	UpdateHPFromDamage(FinalDamage);
	return FinalDamage;
}

void ACMMonster::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ACMMonster::Dead()
{
	Super::Dead();
	UCMPlayerAnimInstance* AnimInstance = Cast<UCMPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if(AnimInstance)
	{
		AnimInstance->PlayDeathMontage();
	}
}

void ACMMonster::ChangeColor(const FGameplayTag& InColor)
{
	CurrentColor = InColor;
	const FLinearColor RealColor = TranslateColor(CurrentColor);
	for(int i=0; i<GetMesh()->GetNumMaterials(); ++i)
	{
		// 각 매터리얼에 설정된 Dynamic 가져오기
		UMaterialInstanceDynamic* Dynamic = Cast<UMaterialInstanceDynamic>(GetMesh()->GetMaterial(i));
		if(Dynamic)
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
			Dynamic->SetVectorParameterValue(TEXT("TimesColor"), RealColor);
		}
	}
}

const FLinearColor& ACMMonster::TranslateColor(const FGameplayTag& ColorTag)
{
	// Tag => LinearColor Value
	if(ColorTag == CM_COLOR_RED)
	{
		return FLinearColor::Red;
	}
	if(ColorTag == CM_COLOR_BLUE)
	{
		return FLinearColor::Blue;
	}
	if(ColorTag == CM_COLOR_GREEN)
	{
		return FLinearColor::Green;
	}
	return FLinearColor::Green;
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
	return 200.0f;
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
	UE_LOG(LogTemp, Warning, TEXT("Monster Attack By AI!"));
	OnAttackFinished.ExecuteIfBound();
}

// // CharacterBase 클래스에서 새로 생성한 가상함수 override (공격이 끝날 때 호출될 예정)
// // AnimNotify 함수라서 자동 호출됨
// void ACMMonster::NotifyComboActionEnd()
// {
// 	Super::NotifyComboActionEnd(); // 아무것도 없음
// 	OnAttackFinished.ExecuteIfBound(); // 델리게이트 바인딩 됐다면, 함수 호출
// }

