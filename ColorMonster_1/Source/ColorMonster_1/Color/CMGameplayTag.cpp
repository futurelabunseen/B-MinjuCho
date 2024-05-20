// Fill out your copyright notice in the Description page of Project Settings.


#include "Color/CMGameplayTag.h"

CMGameplayTag::CMGameplayTag()
{
}

CMGameplayTag::~CMGameplayTag()
{
}

const FLinearColor& CMGameplayTag::TranslateColor(const FGameplayTag& ColorTag)
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