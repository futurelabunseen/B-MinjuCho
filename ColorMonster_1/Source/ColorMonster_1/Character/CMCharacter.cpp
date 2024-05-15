// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CMCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACMCharacter::ACMCharacter()
{

	// Pawn
	/*bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;*/

	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Mesh
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	// HP
	SetMaxHP(100);
	SetCurrentHP(GetMaxHP());
}

// Called when the game starts or when spawned
void ACMCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ACMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ACMCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogTemp, Warning, TEXT("Actor: %s took Damage : %f"), *GetName(), FinalDamage);
	UpdateHPFromDamage(FinalDamage);
	return FinalDamage;
}

void ACMCharacter::UpdateHPFromDamage(float Damage)
{
	CurrentHP -= Damage;
	if(CurrentHP <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor: %s is DEAD"), *GetName());
		Dead();
		SetActorEnableCollision(false);
	}
}

void ACMCharacter::Dead()
{
	
}

void ACMCharacter::Attack()
{
}

