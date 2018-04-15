// Fill out your copyright notice in the Description page of Project Settings.

#include "StealthAI_Character.h"
#include "Engine.h"
#include "StealthAI_Controller.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"


// Sets default values
AStealthAI_Character::AStealthAI_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(90.f);

}

// Called when the game starts or when spawned
void AStealthAI_Character::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensingComp) {
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AStealthAI_Character::OnPlayerCaught);
	}

}

// Called every frame
void AStealthAI_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AStealthAI_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AStealthAI_Character::OnPlayerCaught(APawn * Pawn)
{
	// Get reference from Playter controller
	AStealthAI_Controller* AIController = Cast<AStealthAI_Controller>(GetController());

	if (AIController) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You have been caught"));
		AIController->SetPlayerCaught(Pawn);
	}
}

