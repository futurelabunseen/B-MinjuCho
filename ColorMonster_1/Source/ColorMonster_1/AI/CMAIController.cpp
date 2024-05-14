// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CMAIController.h"

#include "AI/CMAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ACMAIController::ACMAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Script/AIModule.BlackboardData'/Game/AI/CMMonsterData.CMMonsterData'"));
	if(BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/CMMonsterBT.CMMonsterBT'"));
	if(BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}
}

void ACMAIController::RunAI()
{
	// 상위클래스가 기본으로 갖고 있는 변수 Blackboard
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	// 2번째 인자에 넣어서 블랙보드 초기화해줌
	if(UseBlackboard(BBAsset, BlackboardPtr))
	{
		// 블랙보드의 Home Pos 값에다가 현재 위치 넣어주기
		Blackboard->SetValueAsVector(BBKEY_HOMEPOS, GetPawn()->GetActorLocation());
		
		bool RunResult = RunBehaviorTree(BTAsset); // BT 구동
		ensure(RunResult);
	}
}

void ACMAIController::StopAI()
{
	// 현재 동작중인 BT 가져오기
	// 상위클래스가 기본으로 갖고 있는 변수 BrainComponent
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if(BTComponent)
	{
		BTComponent->StopTree(); // 기본값: 안전하다는 옵션 (StopMode = EBTStopMode::Safe)
	}
}

void ACMAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// 빙의 시작 시 구동 시작
	RunAI();
}
