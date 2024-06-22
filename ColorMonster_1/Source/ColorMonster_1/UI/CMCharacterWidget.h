// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CMCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class COLORMONSTER_1_API UCMCharacterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetOwiningActor(AActor* NewOwner) {OwningActor = NewOwner;}
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Actor)
	TObjectPtr<AActor> OwningActor;
};
