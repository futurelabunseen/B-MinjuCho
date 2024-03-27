// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CMCharacterBase.h"
#include "CMCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class COLORMONSTER_PT_API ACMCharacterPlayer : public ACMCharacterBase
{
	GENERATED_BODY()
	
public:
	ACMCharacterPlayer();

protected:
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};
