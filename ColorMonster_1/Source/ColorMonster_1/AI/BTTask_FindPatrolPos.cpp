// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FindPatrolPos.h"

#include "AI/CMAI.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/CMAIInterface.h"

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
}

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	// 현재 Task 실행중인 AI Controller 클래스가 갖고 있는 pawn 가져오기
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(!ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	// 전역함수인 GetNavigationSystem(폰이 위치한 월드)
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (!NavSystem)
	{
		return EBTNodeResult::Failed;
	}

	// 인터페이스 가져오기
	ICMAIInterface* AIInterface = Cast<ICMAIInterface>(ControllingPawn);
	if(!AIInterface)
	{
		return EBTNodeResult::Failed;
	}

	// 현재 AI Controller의 블랙보드 컴포넌트 가져와서 HomePos 벡터값 가져오기
	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BBKEY_HOMEPOS);

	// 반지름 값을 인터페이스 함수를 통해 가져오기
	float PatrolRadius = AIInterface->GetAIPatrolRadius();
	// HomePos 근처 PatrolRadius 반경 내에 랜덤한 포지션 가져오기
	// Out 변수: NextPatrolPos
	FNavLocation NextPatrolPos;
	if(NavSystem->GetRandomPointInNavigableRadius(Origin, PatrolRadius, NextPatrolPos))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(BBKEY_PATROLPOS, NextPatrolPos.Location);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
