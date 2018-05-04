// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NemesisCharacter.generated.h"

UCLASS()
class PROJECTNEMESIS_API ANemesisCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ANemesisCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	class ANemesisAIController* AIController = nullptr;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = AI)
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, Category = AI)
		class UPawnSensingComponent* PawnSensingComp;

private:
	UFUNCTION()
		void OnPlayerCaught(APawn* Pawn);

	// Sensing ---
	FVector PlayerLastKnownLocation;
	bool SeesPlayer = false;
	float sightDelay = 0.f; // Max Time
	float sightTimer = 0.f; // Actual Timer
};
