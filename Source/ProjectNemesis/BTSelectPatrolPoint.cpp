// Fill out your copyright notice in the Description page of Project Settings.

#include "BTSelectPatrolPoint.h"
#include "Engine.h"
#include "StealthAI_PatrolPoint.h"
#include "StealthAI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTSelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AStealthAI_Controller* AICon = Cast<AStealthAI_Controller>(OwnerComp.GetAIOwner());

	if (AICon) {
		// Get BB component
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComponent();

		AStealthAI_PatrolPoint* CurrentPoint = Cast<AStealthAI_PatrolPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

		TArray<AActor*> AvailablePatrolPoints = AICon->GetPatrolPoints();

		AStealthAI_PatrolPoint* NextPatrolPoint = nullptr;

		if (AICon->CurrentPatrolPoint != AvailablePatrolPoints.Num() - 1) {
			NextPatrolPoint = Cast<AStealthAI_PatrolPoint>(AvailablePatrolPoints[++AICon->CurrentPatrolPoint]);
		}
		else { // No more points to go to
			NextPatrolPoint = Cast<AStealthAI_PatrolPoint>(AvailablePatrolPoints[0]);
			AICon->CurrentPatrolPoint = 0;
		}

		BlackboardComp->SetValueAsObject("LocationToGo", NextPatrolPoint);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;

}
