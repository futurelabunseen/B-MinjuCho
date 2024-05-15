// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CMMonsterAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Character/CMMonster.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "Player/CMPlayer.h"

UCMMonsterAnimInstance::UCMMonsterAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMontageRef(TEXT("/Game/Animation/MonsterAttackMontage.MonsterAttackMontage"));
	if(AttackMontageRef.Object)
	{
		AttackMontage = AttackMontageRef.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to call AttackMontage From MonsterAnimInstance"));
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/Game/Animation/MonsterDeadMontage.MonsterDeadMontage"));
	if(DeadMontageRef.Object)
	{
		DeathMontage = DeadMontageRef.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to call DeathMontage From MonsterAnimInstance"));
	}
}

void UCMMonsterAnimInstance::SetMonster(ACMMonster* const InMonster)
{
	Monster = InMonster;
}

void UCMMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UCMMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();
		bIsIdle = GroundSpeed < MovingThreshould;
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould);
	}
}

void UCMMonsterAnimInstance::PlayAttackMontage()
{
	ensure(AttackMontage);
	if(AttackMontage)
	{
		if(!Montage_IsPlaying(AttackMontage))
		{
			Montage_Play(AttackMontage);
		}
	}
}

void UCMMonsterAnimInstance::PlayDeadMontage()
{
	ensure(DeathMontage);
	if(DeathMontage)
	{
		if(!Montage_IsPlaying(DeathMontage))
		{
			Montage_Play(DeathMontage);
		}
	}
}

void UCMMonsterAnimInstance::AnimNotify_EndedAttack()
{
	ensure(Monster);
	if(Monster)
	{
		Monster->AfterAnimEndedAttack();
	}
}

void UCMMonsterAnimInstance::AnimNotify_CheckHit()
{
	ensure(Monster);
	if(Monster)
	{
		Monster->TraceHit();
	}
}

