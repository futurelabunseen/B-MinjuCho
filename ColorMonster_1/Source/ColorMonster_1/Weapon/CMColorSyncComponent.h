// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "CMColorSyncComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COLORMONSTER_1_API UCMColorSyncComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCMColorSyncComponent();
	void CreateDynamicMaterial(UMaterialInterface* InMaterial);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Color, meta = (AllowPrivateAccess = "true"))
	FGameplayTag CurrentColor;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMaterialInstanceDynamic> DynamicInstance;

public:
	UMaterialInstanceDynamic* GetDynamicInstance() { return DynamicInstance; }
	void ChangeColor(const FGameplayTag& InColor);
	
	const FGameplayTag& GetCurrentColor() { return CurrentColor; }

private:
	void SetDynmicInstance(UMaterialInstanceDynamic* InDynamicInstance) { DynamicInstance = InDynamicInstance; }
};
