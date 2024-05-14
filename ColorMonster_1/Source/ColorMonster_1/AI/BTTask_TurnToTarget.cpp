// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_TurnToTarget.h"

#include "AIController.h"
#include "CMAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/CMAIInterface.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	// 현재 BT의 블랙보드에서 타겟 변수(Detect 서비스로 범위 내 감지한 플레이어)
	// 값이 존재한다면
	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if(!Target)
	{
		return EBTNodeResult::Failed;
	}

	// 인터페이스 함수로 지정된 속도 가져오기
	float TurnSpeed = AIInterface->GetAITurnSpeed();
	// 사이 방향 벡터 구하기
	FVector LookVector = Target->GetActorLocation() - ControllingPawn->GetActorLocation();
	// 높이는 무시해도 됨. Turn만 하는 것이므로.
	LookVector.Z = 0.0f;
	// 보간해서 서서히 돌아가도록 (지정된 속도 이용)
	// FRotationMatrix::MakeFromX 기능: Builds a rotation matrix given only a XAxis. Y and Z are unspecified but will be orthonormal. XAxis need not be normalized.
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	ControllingPawn->SetActorRotation(FMath::RInterpTo(ControllingPawn->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), TurnSpeed));

	return EBTNodeResult::Succeeded;
	
}
