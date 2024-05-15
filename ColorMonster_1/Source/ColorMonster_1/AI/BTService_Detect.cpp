// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_Detect.h"

#include "AIController.h"
#include "CMAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/CMAIInterface.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// 폰 정보 가져오기
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(!ControllingPawn)
	{
		return;
	}

	// 폰의 위치와 월드 가져오기
	FVector Center = ControllingPawn->GetActorLocation();
	UWorld* World = ControllingPawn->GetWorld();
	if(!World)
	{
		return;
	}

	// 폰 인터페이스 가져오기
	ICMAIInterface* AIInterface = Cast<ICMAIInterface>(ControllingPawn);
	if(!AIInterface)
	{
		return;
	}

	// 인터페이스로부터 감지 영역 데이터 가져오기
	float DetectRadius = AIInterface->GetAIDetectRange();

	// 감지 방식: Overlap
	// 감지 대상: 여러명 -> TArray
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(SCENE_QUERY_STAT(Detect), false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECC_Pawn,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);
	// Overlap 결과 일어났을 때
	if(bResult)
	{
		// 모든 Overlap 대상들
		for(auto const& OverlapResult : OverlapResults)
		{
			// 감지 대상의 폰을 가져옴
			APawn* Pawn = Cast<APawn>(OverlapResult.GetActor());
			if(Pawn && Pawn->GetController()->IsPlayerController())
			{
				// 감지 대상이 플레이어일 경우
				// 블랙보드의 Target 변수를 해당 플레이어 값을 넣어준다.
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, Pawn);
				// 디버그 구체 그리기
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);

				// 감지 플레이어 사이에 점과 선을 그려준다.
				DrawDebugPoint(World, Pawn->GetActorLocation(), 10.0f, FColor::Green, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), Pawn->GetActorLocation(), FColor::Green, false, 0.27f);
				return;
			}
		}
	}
	// 감지 대상 중에 플레이어가 없으면, 블랙보드 Target 변수 nullptr로 설정 후 빨간 구체
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
	// 디버그 구체 그리기
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}
