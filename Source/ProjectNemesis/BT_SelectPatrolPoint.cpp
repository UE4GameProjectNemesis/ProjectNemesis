// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_SelectPatrolPoint.h"
#include "Engine.h"
#include "NemesisPatrolPoint.h"
#include "NemesisAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBT_SelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ANemesisAIController* AICon = Cast<ANemesisAIController>(OwnerComp.GetAIOwner());
	if (AICon) {
		// Get BB Component
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComponent();
		ANemesisPatrolPoint* CurrentPoint = Cast<ANemesisPatrolPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));
		TArray<AActor*> AvailablePatrolPoints = AICon->GetPatrolPoints(AICon->GetCurrentPathID());
		ANemesisPatrolPoint* NextPatrolPoint = nullptr;

		if (AICon->CurrentPatrolPoint != AvailablePatrolPoints.Num() - 1) {
			NextPatrolPoint = Cast<ANemesisPatrolPoint>(AvailablePatrolPoints[++AICon->CurrentPatrolPoint]);
		}
		else { // After Last Patrol Point
			NextPatrolPoint = Cast<ANemesisPatrolPoint>(AvailablePatrolPoints[0]);
			AICon->CurrentPatrolPoint = 0;
		}

		BlackboardComp->SetValueAsObject("LocationToGo", NextPatrolPoint);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
