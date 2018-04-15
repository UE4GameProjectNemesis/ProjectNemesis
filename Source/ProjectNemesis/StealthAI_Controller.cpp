// Fill out your copyright notice in the Description page of Project Settings.

#include "StealthAI_Controller.h"
#include "Engine.h"
#include "StealthAI_Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "StealthAI_PatrolPoint.h"

AStealthAI_Controller::AStealthAI_Controller()
{
	// initialize BB and BT
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	// initialize BB keys
	PlayerKey = "Target";
	LocationToGoKey = "LocationToGo";

	CurrentPatrolPoint = 0;
}

void AStealthAI_Controller::SetPlayerCaught(APawn * Pawn)
{
	if (BlackboardComp) {
		BlackboardComp->SetValueAsObject(PlayerKey, Pawn);
	}
}

void AStealthAI_Controller::Possess(APawn * Pawn)
{
	Super::Possess(Pawn);

	// Get reference to the character
	AStealthAI_Character* AICharacter = Cast<AStealthAI_Character>(Pawn);

	if (AICharacter) {
		if (AICharacter->BehaviorTree->BlackboardAsset) {
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
		}

		// Populate patrol point array
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStealthAI_PatrolPoint::StaticClass(), PatrolPoints);
		
		BehaviorComp->StartTree(*AICharacter->BehaviorTree);
	}
}

