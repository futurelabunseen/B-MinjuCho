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

	// Set Arrays
	FireMontages.Add(RightFireMontage);
	FireMontages.Add(LeftFireMontage);
	ConvertMontages.Add(RightLeftMontage);
	ConvertMontages.Add(LeftRightMontage);

	// Death Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeathMontageRef(TEXT("/Game/Animation/DeathFWD_Montage.DeathFWD_Montage"));
	if (DeathMontageRef.Object)
	{
		DeathMontage = DeathMontageRef.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FAILED LOADING Death MONTAGE"));
	}
}

void UCMPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACMPlayer>(GetOwningActor());
	if (!Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetOwner is Failed from anim instance"));
	}
}

void UCMPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	//Super::NativeUpdateAnimation(DeltaSeconds);

	
}

uint8 UCMPlayerAnimInstance::PlayShooting(uint8 isLeft)
{
	for(auto ConvertMontage : ConvertMontages)
	{
		if(Montage_IsPlaying(ConvertMontage))
		{
			return 0;
		}
	}
	if (!Montage_IsPlaying(FireMontages[isLeft]))
	{
		Montage_Play(FireMontages[isLeft], 1.0f);
		return 1;
	}
	return 0;
}

uint8 UCMPlayerAnimInstance::PlayConverting(uint8 isLeft)
{
	if (Montage_IsPlaying(FireMontages[isLeft]))
	{
		Montage_Stop(0.0f, FireMontages[isLeft]);
	}

	if (!Montage_IsPlaying(ConvertMontages[isLeft]))
	{
		Montage_Play(ConvertMontages[isLeft], 1.0f);
		return 1;
	}
	return 0;
}

void UCMPlayerAnimInstance::PlayDeathMontage()
{
	if(DeathMontage)
	{
		Montage_Play(DeathMontage);
	}
}
