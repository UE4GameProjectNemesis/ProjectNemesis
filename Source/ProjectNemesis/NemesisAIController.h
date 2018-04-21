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
	UPROPERTY(EditAnywhere, Category = Patrol)
		int32 CurrentPathID = 0;

	virtual void Possess(APawn* Pawn) override;

public:
	ANemesisAIController();

	int32 CurrentPatrolPoint = 0;

	void SetPlayerCaught(APawn* Pawn);
	void SetPlayerLost();

	TArray<AActor*> GetPatrolPoints(int32 ID);

	// Getter Methods
	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }
	FORCEINLINE int32 GetCurrentPathID() const { return CurrentPathID; }

	FORCEINLINE FName GetPlayerKey() { return PlayerKey; }
	UObject* GetPlayerObject();
	// Setter Methods
	FORCEINLINE void SetCurrentPathID(int32 newPathID) { CurrentPathID = newPathID; }

};
