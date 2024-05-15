// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_AttackInRange.h"

#include "AIController.h"
#include "CMAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/CMAIInterface.h"

UBTDecorator_AttackInRange::UBTDecorator_AttackInRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_AttackInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	// 폰 정보 가져오기
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(!ControllingPawn)
	{
		return false;
	}

	// 폰 인터페이스 가져오기
	ICMAIInterface* AIInterface = Cast<ICMAIInterface>(ControllingPawn);
	if(!AIInterface)
	{
		return false;
	}

	// 현재 BT의 블랙보드에서 타겟 변수(Detect 서비스로 범위 내 감지한 플레이어)
	// 값이 존재한다면
	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if(!Target)
	{
		return false;
	}

	bool IsAttacking = OwnerComp.GetBlackboardComponent()->GetValueAsBool(BBKEY_ISATTACKING);
	if(IsAttacking)
	{
		return false;
	}
	
	// AI 폰과 타겟 거리 구하고, 
	// AI 폰의 인터페이스를 통한 공격범위값
	// 내에 있으면 true, 아니면 false 반환
	float DistanceToTarget = ControllingPawn->GetDistanceTo(Target);
	float AttackRangeWithRadius = AIInterface->GetAIAttackRange();
	bResult = (DistanceToTarget <= AttackRangeWithRadius);
	return bResult;
}
