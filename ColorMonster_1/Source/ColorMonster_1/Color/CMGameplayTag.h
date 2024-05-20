// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameplayTags.h"

#define CM_COLOR_NONE FGameplayTag::RequestGameplayTag(FName("Color.None"))
#define CM_COLOR_RED FGameplayTag::RequestGameplayTag(FName("Color.Red"))
#define CM_COLOR_GREEN FGameplayTag::RequestGameplayTag(FName("Color.Green"))
#define CM_COLOR_BLUE FGameplayTag::RequestGameplayTag(FName("Color.Blue"))

/**
 * 
 */
class COLORMONSTER_1_API CMGameplayTag
{
public:
	CMGameplayTag();
	~CMGameplayTag();
	static const FLinearColor& TranslateColor(const FGameplayTag& ColorTag);
};
