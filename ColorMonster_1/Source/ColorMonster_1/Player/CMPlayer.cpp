// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CMPlayer.h"

#include "Camera/CameraComponent.h"
#include "Animation/AnimInstance.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"

#include "Animation/CMPlayerAnimInstance.h"
#include "Components/SphereComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "UI/CMWidgetComponent.h"
#include "Weapon/CMWeapon.h"
#include "Weapon/CMLineGun.h"
#include "Weapon/CMColorGun.h"

ACMPlayer::ACMPlayer()
{
	// Create a Camera
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("FX_Head"));
	//FirstPersonCameraComponent->SetupAttachment(RootComponent);
	//FirstPersonCameraComponent->SetRelativeLocation(FVector(12.0f, -5.0f, 72.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonTwinblast/Characters/Heroes/TwinBlast/Meshes/TwinBlast.TwinBlast'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}
	
	GetMesh()->HideBoneByName(TEXT("head"), PBO_None);
	GetCapsuleComponent()->BodyInstance.SetCollisionProfileName(TEXT("Player"));
	
	// Animation
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/ParagonTwinblast/Characters/Heroes/TwinBlast/Twinblast_AnimBlueprint.Twinblast_AnimBlueprint_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to call anim instance class From Player"));
	}
	//GetMesh()->SetupAttachment(RootComponent);
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));

	// Input
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/FirstPerson/Input/IMC_Default.IMC_Default'"));
	if (nullptr != InputMappingContextRef.Object)
	{
		DefaultMappingContext = InputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_Move.IA_Move'"));
	if (nullptr != InputActionMoveRef.Object)
	{
		MoveAction = InputActionMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_Jump.IA_Jump'"));
	if (nullptr != InputActionJumpRef.Object)
	{
		JumpAction = InputActionJumpRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_Look.IA_Look'"));
	if (nullptr != InputActionLookRef.Object)
	{
		LookAction = InputActionLookRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionFireRef(TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_Shoot.IA_Shoot'"));
	if (nullptr != InputActionFireRef.Object)
	{
		FireAction = InputActionFireRef.Object;
	}

	isLeft = EGunHandler::Right;

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionConvertRef(TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_Convert.IA_Convert'"));
	if (nullptr != InputActionConvertRef.Object)
	{
		ConvertAction = InputActionConvertRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionReloadRef(TEXT("/Script/EnhancedInput.InputAction'/Game/FirstPerson/Input/Actions/IA_Reload.IA_Reload'"));
	if (nullptr != InputActionReloadRef.Object)
	{
		ReloadAction = InputActionReloadRef.Object;
	}

	// Weapon Class
	// Right Weapon
	static ConstructorHelpers::FClassFinder<ACMLineGun> RightGunRef (TEXT("/Game/Blueprint/BP_LineGun.BP_LineGun_C"));
	if(RightGunRef.Class)
	{
		RightGunClass = RightGunRef.Class;
	}
	
	// Left Weapon
	static ConstructorHelpers::FClassFinder<ACMColorGun> LeftGunRef (TEXT("/Game/Blueprint/BP_CMColorGun.BP_CMColorGun_C"));
	if(LeftGunRef.Class)
	{
		LeftGunClass = LeftGunRef.Class;
	}
	
	// Custom Anim Instance
	PlayerAnimInstance = Cast<UCMPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	// Big Size of Monster Collision against Monster
	SecondCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SecondCollisionComponent"));
	SecondCollisionComponent->SetCollisionProfileName(TEXT("Player"));
	SecondCollisionComponent->SetWorldScale3D(FVector(3.0f, 3.0f, 3.0f));
}

void ACMPlayer::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	HpBar->SetVisibility(false);
	GetMesh()->HideBoneByName(TEXT("head"), PBO_None);
	
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	RightGun = GetWorld()->SpawnActor<ACMLineGun>(RightGunClass);
	ensure(RightGun);
	// Equip Weapon Mesh
	if (RightGun)
	{
		// Material Visibility = None
		// If you want change weapon Mesh, here
		// FVector SocketLocation = GetMesh()->GetSocketLocation(FName("Muzzle_R"));
		// WeaponMesh->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, AttachPoint);
		// WeaponMesh->SetRelativeLocation(WeaponRelativeLocation);
		// WeaponMesh->SetRelativeRotation(WeaponRotator);
		// WeaponMesh->CastShadow = true;
		// WeaponMesh->bCastHiddenShadow = true;
		RightGun->SetPlayer(this);
	}

	// 왼쪽 기존 총 없애기
	if (USkeletalMeshComponent* SkeletalMeshComp = GetMesh())
	{
		// 본을 숨기기 
		SkeletalMeshComp->HideBoneByName("weapon_l", EPhysBodyOp::PBO_None);
	}
	
	// Spawn LeftGun Actor & Attach to Socket
	LeftGun = GetWorld()->SpawnActor<ACMColorGun>(LeftGunClass);
	
	ensure(LeftGun);
	if (LeftGun)
	{
		FName SocketName = FName("Muzzle_L");
		if(GetMesh()->DoesSocketExist(SocketName))
		{
			const USkeletalMeshSocket* ColorGunMesh = (GetMesh()->GetSocketByName(SocketName));
			if (ColorGunMesh)
			{
				ColorGunMesh->AttachActor(LeftGun, GetMesh());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed Attaching ColorGun in Player"));
			}
		}
		// Material Visibility = None
		// If you want change weapon Mesh, here
		// FVector SocketLocation = GetMesh()->GetSocketLocation(FName("Muzzle_R"));
		// WeaponMesh->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, AttachPoint);
		// WeaponMesh->SetRelativeLocation(WeaponRelativeLocation);
		// WeaponMesh->SetRelativeRotation(WeaponRotator);
		// WeaponMesh->CastShadow = true;
		// WeaponMesh->bCastHiddenShadow = true;
		LeftGun->SetPlayer(this);

		// For Binding with Spawned LeftGun
		OnSetGun.Broadcast();
		
		// Update Bullet UI
		LeftGun->OnBulletChanged.Broadcast(LeftGun->GetCurrentBullet(), LeftGun->GetMaxBullet());
		RightGun->OnBulletChanged.Broadcast(RightGun->GetCurrentBullet(), RightGun->GetMaxBullet());
		OnConvertedGun.Broadcast((uint8)isLeft);
	}

	// 총 교체를 위한 총 배열 관리
	ArrayGun.Add(RightGun);
	ArrayGun.Add(LeftGun);

	Gun = ArrayGun[0];
}

void ACMPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACMPlayer::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACMPlayer::Look);

		// Fire
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ACMPlayer::Fire);

		// Converting Gun
		EnhancedInputComponent->BindAction(ConvertAction, ETriggerEvent::Triggered, this, &ACMPlayer::ConvertingGun);

		// Reload
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &ACMPlayer::Reload);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ACMPlayer::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.X);
		AddMovementInput(GetActorRightVector(), MovementVector.Y);
	}
}

void ACMPlayer::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACMPlayer::Fire()
{
	if(Gun)
	{
		Gun->Fire();
	}
}

void ACMPlayer::ConvertingGun()
{
	if(!PlayerAnimInstance)
	{
		PlayerAnimInstance = Cast<UCMPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	}
	if (PlayerAnimInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to cast anim instance"));
		return;
	}
	if(PlayerAnimInstance->PlayConverting((uint8)isLeft) == 1)
	{
		switch(isLeft)
		{
		case EGunHandler::Right:
			isLeft = EGunHandler::Left;
			break;
		case EGunHandler::Left:
			isLeft = EGunHandler::Right;
			break;
		}
		Gun = ArrayGun[(uint8)isLeft];
		OnConvertedGun.Broadcast((uint8)isLeft);
	}
	UE_LOG(LogTemp, Warning, TEXT("Converting Gun!: %d"), isLeft);
}

void ACMPlayer::Reload()
{
	if(Gun)
	{
		Gun->Reload();
	}
}
