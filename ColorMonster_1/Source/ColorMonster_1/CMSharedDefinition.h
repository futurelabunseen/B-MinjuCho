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
#define CM_COLOR_PURPLE FGameplayTag::RequestGameplayTag(FName("Color.Purple"))
#define CM_COLOR_PINK FGameplayTag::RequestGameplayTag(FName("Color.Pink"))
#define CM_COLOR_YELLOW FGameplayTag::RequestGameplayTag(FName("Color.Yellow"))
#define CM_COLOR_GRAY FGameplayTag::RequestGameplayTag(FName("Color.Gray"))
#define CM_COLOR_ORANGE FGameplayTag::RequestGameplayTag(FName("Color.Orange"))
#define CM_COLOR_BLACK FGameplayTag::RequestGameplayTag(FName("Color.Black"))

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
		static const FLinearColor PurpleColor = FLinearColor(FVector(0.5f, 0.f, 1.0f));
		static const FLinearColor PinkColor = FLinearColor(FVector(1.0f, 0.f, 1.0f));
		static const FLinearColor OrangeColor = FLinearColor(FVector(1.0f, 0.5f, 0.0f));
		static const FLinearColor DeepGrayColor = FLinearColor(FVector(0.8f, 0.8f, 0.8f));
		
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
		if(ColorTag == CM_COLOR_PURPLE)
		{
			return PurpleColor;
		}
		if(ColorTag == CM_COLOR_PINK)
		{
			return PinkColor;
		}
		if(ColorTag == CM_COLOR_YELLOW)
		{
			return FLinearColor::Yellow;
		}
		if(ColorTag == CM_COLOR_GRAY)
		{
			return DeepGrayColor;
		}
		if(ColorTag == CM_COLOR_ORANGE)
		{
			return OrangeColor;
		}
		if(ColorTag == CM_COLOR_BLACK)
		{
			return FLinearColor::Black;
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
		if(ColorTag == CM_COLOR_PURPLE)
		{
			return FText::FromString("PURPLE");
		}
		if(ColorTag == CM_COLOR_PINK)
		{
			return FText::FromString("PINK");
		}
		if(ColorTag == CM_COLOR_YELLOW)
		{
			return FText::FromString("YELLOW");
		}
		if(ColorTag == CM_COLOR_GRAY)
		{
			return FText::FromString("GRAY");
		}
		if(ColorTag == CM_COLOR_ORANGE)
		{
			return FText::FromString("ORANGE");
		}
		if(ColorTag == CM_COLOR_BLACK)
		{
			return FText::FromString("BLACK");
		}
		return FText::FromString("NONE");
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

	static const TArray<FGameplayTag>& GetCategoriesPerLevel(int32 InCode)
	{
		// 이게 아니라 그냥 static const TArray<FGameplayTag> 하나 만들어놓고, 비트에 따라 해당 인덱스 검색하게끔 해야함
		static const TArray<FGameplayTag> BaseOnly = {CM_MONSTER_BASE};
		static const TArray<FGameplayTag> CardboardOnly = {CM_MONSTER_CARDBOARD};
		static const TArray<FGameplayTag> BaseCardboard = {CM_MONSTER_BASE, CM_MONSTER_CARDBOARD};
		switch (InCode)
		{
		case 1:
			return BaseOnly;
		case 2:
			return CardboardOnly;
		case 4:
			return BaseCardboard;
		default:
			return BaseOnly;
		}
	}
};
