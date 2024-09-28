// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CMSharedDefinition.h"
#include "CMGameMode.generated.h"

/**
 * 
 */
UCLASS()
class COLORMONSTER_1_API ACMGameMode : public AGameMode
{
	GENERATED_BODY()
	

public:
	ACMGameMode();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

// Login
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void StartPlay() override;
// Time
private:
	void UpdateTime(float DeltaSeconds);

	UPROPERTY()
	float LimitTimePerThisLevel;
	
	UPROPERTY()
	float CurrentLeftTime;
public:
	void InitializeTime();

// UI
private:
	UPROPERTY(EditAnywhere, Blueprintable, Category = "UI")
	TSubclassOf<UUserWidget> WidgetClass;



// Game Object Data
public:
	float GetLimitTime() const;

private:
	UPROPERTY()
	TObjectPtr<class UCMGameInstance> CMGameInstance;

	UPROPERTY()
	TObjectPtr<class ACMGameState> CMGameState;

	

// Next Level
public:
	void SetLevelAndLoad(int32 InLevel = -1);

};
