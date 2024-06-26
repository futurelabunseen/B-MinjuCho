// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CMCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/CMHpBarWidget.h"
#include "UI/CMWidgetComponent.h"

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

	// HP Widget
	HpBar = CreateDefaultSubobject<UCMWidgetComponent>(TEXT("Widget"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	static ConstructorHelpers::FClassFinder<UUserWidget> HpBarWidgetRef(TEXT("/Game/Blueprint/UI/WBP_CMHPBar.WBP_CMHPBar_C"));
	if (HpBarWidgetRef.Class)
	{
		HpBar->SetWidgetClass(HpBarWidgetRef.Class);
		HpBar->SetWidgetSpace(EWidgetSpace::World);
		HpBar->SetDrawSize(FVector2D(150.0f, 15.0f));
		// 3D 공간에서 평면으로 렌더링
		HpBar->SetGeometryMode(EWidgetGeometryMode::Plane);
		// 고정된 크기로 렌더링
		HpBar->SetDrawAtDesiredSize(false);
		HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		// 3D 공간에서 원래 크기로 렌더링되도록 설정
		HpBar->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));

		// 그림자 끄기
		HpBar->CastShadow = false;
		HpBar->bCastDynamicShadow = false;
		HpBar->bAffectDynamicIndirectLighting = false;
		HpBar->bAffectDistanceFieldLighting = false;
	}
}

// Called when the game starts or when spawned
void ACMCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(HpBar)
	{
		HpBar->InitWidget();
		
	}
}


// Called to bind functionality to input
void ACMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACMCharacter::SetupCharacterWidget(UCMCharacterWidget* InCharacterWidget)
{
	UCMHpBarWidget* HpBarWidget = Cast<UCMHpBarWidget>(InCharacterWidget);
	if(HpBarWidget)
	{
		HpBarWidget->SetMaxHp(GetMaxHP());
		HpBarWidget->UpdateHpBar(GetCurrentHP());
		OnHpChanged.AddDynamic(HpBarWidget, &UCMHpBarWidget::UpdateHpBar);
	}
}

float ACMCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                               AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	CurrentHP -= FinalDamage;
	OnHpChanged.Broadcast(CurrentHP);
	UE_LOG(LogTemp, Warning, TEXT("Actor: %s took Damage : %f"), *GetName(), FinalDamage);
	//UpdateHPFromDamage(FinalDamage);
	return FinalDamage;
}

void ACMCharacter::UpdateHPFromDamage(float Damage)
{
	
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

