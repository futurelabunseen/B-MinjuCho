// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CMCharacterBase.h"

// Sets default values
ACMCharacterBase::ACMCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACMCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACMCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACMCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

