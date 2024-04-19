// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CMPlayerAnimInstance.h"

#include "Player/CMPlayer.h"

UCMPlayerAnimInstance::UCMPlayerAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> RightFireMontageRef(TEXT("/Game/Animation/Fire_Rt_Montage.Fire_Rt_Montage"));
	if (RightFireMontageRef.Object)
	{
		RightFireMontage = RightFireMontageRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> LeftFireMontageRef(TEXT("/Game/Animation/Fire_Lft_Montage.Fire_Lft_Montage"));
	if (LeftFireMontageRef.Object)
	{
		LeftFireMontage = LeftFireMontageRef.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FAILED LOADING LEFTFIRE MONTAGE"));
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> RightLeftMontageRef(TEXT("/Game/Animation/RightLeft_Montage.RightLeft_Montage"));
	if (RightLeftMontageRef.Object)
	{
		RightLeftMontage = RightLeftMontageRef.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FAILED LOADING RightLeft MONTAGE"));
	}
	LeftRightMontage = RightLeftMontageRef.Object;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> LeftRightMontageRef(TEXT("/Game/Animation/RightLeft_Montage.RightLeft_Montage"));
	if (LeftRightMontageRef.Object)
	{
		LeftRightMontage = LeftRightMontageRef.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FAILED LOADING LeftRight MONTAGE"));
	}
}

void UCMPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACMPlayer>(GetOwningActor());
	if (Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetOwner SUCCESS"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GetOwner is Failed from anim instance"));
	}
}

void UCMPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	//Super::NativeUpdateAnimation(DeltaSeconds);

	
}

void UCMPlayerAnimInstance::PlayShooting()
{
	if (!Montage_IsPlaying(RightFireMontage) && Owner->isLeft == 0)
	{
		Montage_Play(RightFireMontage, 1.0f);
	}
	if (!Montage_IsPlaying(LeftFireMontage) && Owner->isLeft == 1)
	{
		Montage_Play(LeftFireMontage, 1.0f);
	}
}

void UCMPlayerAnimInstance::PlayConverting()
{
	if (Owner->isLeft == 0)
	{
		if (Montage_IsPlaying(RightFireMontage))
		{
			Montage_Stop(0.0f, RightFireMontage);
		}
		Owner->isLeft = 1;

		if (!Montage_IsPlaying(RightLeftMontage))
		{
			Montage_Play(RightLeftMontage, 1.0f);
		}
	}
	else if (Owner->isLeft == 1)
	{
		if (Montage_IsPlaying(LeftFireMontage))
		{
			Montage_Stop(0.0f, LeftFireMontage);
		}
		Owner->isLeft = 0;

		if (!Montage_IsPlaying(LeftRightMontage))
		{
			Montage_Play(LeftRightMontage, 1.0f);
		}
	}
}
