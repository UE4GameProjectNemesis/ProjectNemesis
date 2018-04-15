// Fill out your copyright notice in the Description page of Project Settings.

#include "NemesisAIController.h"
#include "Engine.h"
#include "NemesisCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "NemesisPatrolPoint.h"

ANemesisAIController::ANemesisAIController()
{
	// initialize BB and BT
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	// initialize BB keys
	PlayerKey = "Target";
	LocationToGoKey = "LocationToGo";

	CurrentPatrolPoint = 0;
}

void ANemesisAIController::SetPlayerCaught(APawn * Pawn)
{
	if (BlackboardComp) {
		BlackboardComp->SetValueAsObject(PlayerKey, Pawn);
	}
}

void ANemesisAIController::Possess(APawn * Pawn)
{
	Super::Possess(Pawn);

	// Get character references
	ANemesisCharacter* AICharacter = Cast<ANemesisCharacter>(Pawn);
	if (AICharacter) {
		if (AICharacter->BehaviorTree->BlackboardAsset) {
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
		}
	}

	// Populate patrol points array
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANemesisPatrolPoint::StaticClass(), PatrolPoints);
	
	BehaviorComp->StartTree(*AICharacter->BehaviorTree);
}

