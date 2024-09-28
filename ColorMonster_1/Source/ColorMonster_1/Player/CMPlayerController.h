// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CMPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class COLORMONSTER_1_API ACMPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	// For Network
protected:
	virtual void PostInitializeComponents() override;
	virtual void PostNetInit() override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
public:
	void SetPlayerInputMode(bool bInputMode);
};
