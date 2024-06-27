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
struct FInfoPerMonster
{
	
	GENERATED_BODY()
	

	FInfoPerMonster()
	{
		Color = CM_COLOR_RED;
		LeftOver = -1;
		SpawnNum = -1;
	}

	FInfoPerMonster (FGameplayTag InColor, int32 InLeftOver, int32 InSpawnNum) : Color(InColor), LeftOver(InLeftOver), SpawnNum(InSpawnNum) {}
	
	UPROPERTY()
	
	FGameplayTag Color;
    
	UPROPERTY()
	
	int32 LeftOver;

	UPROPERTY()

	int32 SpawnNum;
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

	static const FGameplayTag& StringToColorTag(const FString& InString)
	{
		static const FGameplayTag Red = CM_COLOR_RED;
		static const FGameplayTag Blue = CM_COLOR_BLUE;
		static const FGameplayTag Green = CM_COLOR_GREEN;
		static const FGameplayTag Purple = CM_COLOR_PURPLE;
		static const FGameplayTag Pink = CM_COLOR_PINK;
		static const FGameplayTag Yellow = CM_COLOR_YELLOW;
		static const FGameplayTag Gray = CM_COLOR_GRAY;
		static const FGameplayTag Orange = CM_COLOR_ORANGE;
		static const FGameplayTag Black = CM_COLOR_BLACK;
		static const FGameplayTag None = CM_COLOR_NONE;
		// FString => Tag Value
		if(InString == TEXT("Color.Red"))
		{
			return Red;
		}
		if(InString == TEXT("Color.Blue"))
		{
			return Blue;
		}
		if(InString == TEXT("Color.Green"))
		{
			return Green;
		}
		if(InString == TEXT("Color.Purple"))
		{
			return Purple;
		}
		if(InString == TEXT("Color.Pink"))
		{
			return Pink;
		}
		if(InString == TEXT("Color.Yellow"))
		{
			return Yellow;
		}
		if(InString == TEXT("Color.Gray") || InString == TEXT("Color.Grey"))
		{
			return Gray;
		}
		if(InString == TEXT("Color.Orange"))
		{
			return Orange;
		}
		if(InString == TEXT("Color.Black"))
		{
			return Black;
		}
		return None;
	}
	static const FGameplayTag& StringToMonsterTag(const FString& InString)
	{
		static const FGameplayTag Base = CM_MONSTER_BASE;
		static const FGameplayTag Cardboard = CM_MONSTER_CARDBOARD;
		// FString => Tag Value
		if(InString == TEXT("Monster.Base"))
		{
			return Base;
		}
		if(InString == TEXT("Monster.Cardboard"))
		{
			return Cardboard;
		}
		
		return Base;
	}
};
