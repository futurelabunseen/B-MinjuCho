// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CMFPSHUD.generated.h"

/**
 * 
 */
UCLASS()
class COLORMONSTER_1_API ACMFPSHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTexture2D> CrosshairTexture;

public:
	ACMFPSHUD();
	virtual void DrawHUD() override;
};
