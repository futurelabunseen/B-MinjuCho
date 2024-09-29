// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/CMColorSyncComponent.h"
#include "CMSharedDefinition.h"

// Sets default values for this component's properties
UCMColorSyncComponent::UCMColorSyncComponent()
{
	CurrentColor = CM_COLOR_NONE;
}

void UCMColorSyncComponent::CreateDynamicMaterial(UMaterialInterface* InMaterial)
{
	if (InMaterial)
	{
		UMaterialInstanceDynamic* TempDynmaicInstance = Cast<UMaterialInstanceDynamic>(InMaterial);
		if (TempDynmaicInstance)
		{
			SetDynmicInstance(TempDynmaicInstance);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UCMColorSyncComponent::Failed to CreateDynamicMaterial"));
	}
}

void UCMColorSyncComponent::ChangeColor(const FGameplayTag& InColor)
{
	CurrentColor = InColor;
	const FLinearColor RealColor = CMSharedDefinition::TranslateColor(CurrentColor);
	if (DynamicInstance)
	{
		// 현재 컬러로 곱하기
		DynamicInstance->SetVectorParameterValue(FName("Tint"), RealColor);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UCMColorSyncComponent::Failed to Load DynmaicMaterial"));
	}
}
