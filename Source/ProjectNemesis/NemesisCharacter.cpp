// Fill out your copyright notice in the Description page of Project Settings.

#include "NemesisCharacter.h"
#include "Engine.h"
#include "NemesisAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ANemesisCharacter::ANemesisCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingCom"));
	PawnSensingComp->SetPeripheralVisionAngle(60.f);
}

// Called when the game starts or when spawned
void ANemesisCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensingComp) {
		PawnSensingComp->OnSeePawn.AddDynamic(this, &ANemesisCharacter::OnPlayerCaught);
	}

}

// Called every frame
void ANemesisCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANemesisCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANemesisCharacter::OnPlayerCaught(APawn * Pawn)
{
	ANemesisAIController* AIController = Cast<ANemesisAIController>(GetController());

	if (AIController) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Player Caught"));
		AIController->SetPlayerCaught(Pawn);
	}
}

