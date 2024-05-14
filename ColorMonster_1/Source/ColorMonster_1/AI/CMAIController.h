// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CMAIController.generated.h"

/**
 * 
 */
UCLASS()
class COLORMONSTER_1_API ACMAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACMAIController();

	void RunAI(); // AI 구동시키는 함수
	void StopAI(); // AI 멈추는 함수

protected:
	virtual void OnPossess(APawn* InPawn) override; // Pawn이 빙의했을 때 (컨트롤러 제공 함수)

private:
	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset;
};
