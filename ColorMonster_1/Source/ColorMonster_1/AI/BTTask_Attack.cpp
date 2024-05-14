// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Attack.h"

#include "AIController.h"
#include "Interface/CMAIInterface.h"

UBTTask_Attack::UBTTask_Attack()
{
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	// 폰 정보 가져오기
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(!ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	// 폰 인터페이스 가져오기
	ICMAIInterface* AIInterface = Cast<ICMAIInterface>(ControllingPawn);
	if (nullptr == AIInterface)
	{
		return EBTNodeResult::Failed;
	}

	// 인터페이스에 정의된 델리게이트 타입으로 선언 
	FAICharacterAttackFinished OnAttackFinished;

	// 델리게이트 함수에 원하는 함수 묶기!
	OnAttackFinished.BindLambda(
		[&]()
		{
			// 델리게이트 함수에서 호출할 예정이다.
			// 기본적으로 ExecuteTask 함수가 리턴된 후, Task 끝내려면 호출되어야 하는 함수 (성공으로)
			UE_LOG(LogTemp, Warning, TEXT("Finished Monster Attack Task."));
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);
	
	// 델리게이트 Pawn에게 넘겨준 후
	// 공격 수행
	AIInterface->SetAIAttackDelegate(OnAttackFinished);
	AIInterface->AttackByAI();

	// 아직 실행 중
	return EBTNodeResult::InProgress;
	// 델리게이트로 FinishLatentTask 넘겨줬으니까 공격 끝날 시 자동으로 성공 함수가 실행될 것임.
}
