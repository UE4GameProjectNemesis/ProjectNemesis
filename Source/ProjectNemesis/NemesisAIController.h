// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NemesisAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNEMESIS_API ANemesisAIController : public AAIController
{
	GENERATED_BODY()

	class UBehaviorTreeComponent* BehaviorComp;
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditAnywhere, Category = AI)
		FName LocationToGoKey;
	UPROPERTY(EditAnywhere, Category = AI)
		FName PlayerKey;

	TArray<AActor*> PatrolPoints;

	virtual void Possess(APawn* Pawn) override;

public:
	ANemesisAIController();

	int32 CurrentPatrolPoint = 0;

	void SetPlayerCaught(APawn* Pawn);

	// Inline Getter Methods
	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }

};
