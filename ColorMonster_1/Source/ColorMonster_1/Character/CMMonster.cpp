// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CMMonster.h"

#include "Animation/CMPlayerAnimInstance.h"
#include "GameplayTagContainer.h"
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
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	CurrentColor = CM_COLOR_NONE;

	for(int i=0; i<GetMesh()->GetNumMaterials();++i)
	{
		GetMesh()->CreateDynamicMaterialInstance(i, nullptr);
	}
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
	UE_LOG(LogTemp, Warning, TEXT("Monster::GetNumMaterials: %d"), GetMesh()->GetNumMaterials());
	for(int i=0; i<GetMesh()->GetNumMaterials(); ++i)
	{
		UMaterialInstanceDynamic* Dynamic = Cast<UMaterialInstanceDynamic>(GetMesh()->GetMaterial(i));
		if(Dynamic)
		{
			// 전체 훑는 방법
			// TArray<FMaterialParameterInfo> MaterialParameters;
			// TArray<FGuid> Guid;
			// Dynamic->GetAllVectorParameterInfo(MaterialParameters, Guid);
			// for(FMaterialParameterInfo MaterialParam : MaterialParameters)
			// {
			// 	Dynamic->SetVectorParameterValueByInfo(MaterialParam, RealColor);
			// }
			
			Dynamic->SetVectorParameterValue(TEXT("TimesColor"), RealColor);
		}
	}
}

const FLinearColor& ACMMonster::TranslateColor(const FGameplayTag& ColorTag) const
{
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



