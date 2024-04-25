// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CMMonster.h"

#include "Animation/CMPlayerAnimInstance.h"
#include "GameplayTagContainer.h"
#include "Color/CMGameplayTag.h"
#include "GameplayTags.h"

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
	CurrentColor = TEXT("Blue");
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
	
	//CurrentColor = FGameplayTag::EmptyTag;
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
//
//void ACMMonster::ChangeColor(const FGameplayTag& InColor)
//{
//	CurrentColor = InColor;
//}
