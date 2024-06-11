// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CMCharacter.h"
#include "InputActionValue.h"
#include "CMPlayer.generated.h"

UENUM()
enum class EGunHandler : uint8
{
	Right,
	Left
};


class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSetGun);

UCLASS()
class COLORMONSTER_1_API ACMPlayer : public ACMCharacter
{
	GENERATED_BODY()
	
public:

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

	ACMPlayer();
	
protected:
	// Add Input Mapping Context
	virtual void BeginPlay() override;

// Input Section
protected:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	/** Converting Gun Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ConvertAction;

	/** Reload Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ReloadAction;



public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCMPlayerAnimInstance> PlayerAnimInstance;

// Gun Section
public:
	// Delegate Instance for HUD Binding
	FOnSetGun OnSetGun;
	
	UPROPERTY(EditAnywhere)
	EGunHandler isLeft;

	void Fire();

	void ConvertingGun();

	void Reload();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gun, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ACMLineGun> RightGunClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gun, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ACMLineGun> RightGun;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gun, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ACMColorGun> LeftGunClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gun, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ACMColorGun> LeftGun;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gun, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ACMWeapon> Gun;

private:
	UPROPERTY()
	TArray<class ACMWeapon*> ArrayGun;

public:
	const TObjectPtr<class ACMColorGun>& GetLeftGun() const { return LeftGun; }
	const TObjectPtr<class ACMLineGun>& GetRightGun() const { return RightGun; }
};
