// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"

#include "CMWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class COLORMONSTER_1_API UCMWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	virtual void InitWidget() override;
};