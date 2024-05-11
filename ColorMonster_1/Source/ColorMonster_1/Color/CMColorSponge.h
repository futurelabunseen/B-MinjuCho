// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "CMColorSponge.generated.h"

UCLASS()
class COLORMONSTER_1_API ACMColorSponge : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACMColorSponge();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE const FGameplayTag& GetCurrentColor() const { return CurrentColor; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Color, meta = (AllowPrivateAccess = "true"))
	FGameplayTag CurrentColor;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "StaticMesh")
	TObjectPtr<class UStaticMeshComponent> StaticMesh;

	UFUNCTION(BlueprintCallable)
	void ChangeColor(const FGameplayTag& InColor);
};
