// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameplayTags.h"
#include "CMSharedDefinition.generated.h"

#define CM_COLOR_NONE FGameplayTag::RequestGameplayTag(FName("Color.None"))
#define CM_COLOR_RED FGameplayTag::RequestGameplayTag(FName("Color.Red"))
#define CM_COLOR_GREEN FGameplayTag::RequestGameplayTag(FName("Color.Green"))
#define CM_COLOR_BLUE FGameplayTag::RequestGameplayTag(FName("Color.Blue"))

#define CM_MONSTER_BASE FGameplayTag::RequestGameplayTag(FName("Monster.Base"))
#define CM_MONSTER_CARDBOARD FGameplayTag::RequestGameplayTag(FName("Monster.Cardboard"))

USTRUCT()
struct FInfoPerColor
{
	
	GENERATED_BODY()
	

	FInfoPerColor()
	{
		Color = CM_COLOR_RED;
		LeftOver = -1;
	}

	FInfoPerColor (FGameplayTag InColor, int32 InLeftOver) : Color(InColor), LeftOver(InLeftOver) {}
	
	UPROPERTY()
	
	FGameplayTag Color;
    
	UPROPERTY()
	
	int32 LeftOver;
};

/**
 * 
 */
class COLORMONSTER_1_API CMSharedDefinition
{
public:
	CMSharedDefinition();
	~CMSharedDefinition();
	
	static const FLinearColor& TranslateColor(const FGameplayTag& ColorTag)
	{
		// Tag => LinearColor Value
		if(ColorTag == CM_COLOR_RED)
		{
			return FLinearColor::Red;
		}
		if(ColorTag == CM_COLOR_BLUE)
		{
			return FLinearColor::Blue;
		}
		if(ColorTag == CM_COLOR_GREEN)
		{
			return FLinearColor::Green;
		}
		return FLinearColor::White;
	}

	static const FText ColorTagToText(const FGameplayTag& ColorTag)
	{
		// Tag => FText Value
		if(ColorTag == CM_COLOR_RED)
		{
			return FText::FromString("RED");
		}
		if(ColorTag == CM_COLOR_BLUE)
		{
			return FText::FromString("BLUE");
		}
		if(ColorTag == CM_COLOR_GREEN)
		{
			return FText::FromString("GREEN");
		}
		return FText::FromString("WHITE");
	}

	static const FText MonsterTagToText(const FGameplayTag& ColorTag)
	{
		// Tag => FText Value
		if(ColorTag == CM_MONSTER_BASE)
		{
			return FText::FromString("DEFAULT");
		}
		if(ColorTag == CM_MONSTER_CARDBOARD)
		{
			return FText::FromString("CARDBOARD");
		}
		return FText::FromString("NONE");
	}
};
