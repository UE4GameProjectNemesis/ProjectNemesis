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
	
	// Sensing Setup
	if (PawnSensingComp) {
		PawnSensingComp->OnSeePawn.AddDynamic(this, &ANemesisCharacter::OnPlayerCaught);
		sightDelay = PawnSensingComp->SensingInterval + 0.1f; // Needs to be slighlty bigger than the actual sensing interval
	}
	// Controller Setup
	AIController = Cast<ANemesisAIController>(GetController());


}

// Called every frame
void ANemesisCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AIController) {
		AActor* PlayerA = Cast<AActor>(AIController->GetPlayerObject());
		if (PlayerA) {
			PlayerLastKnownLocation = PlayerA->GetTransform().GetLocation();
			// Lose player whenever OnSeePawn() -> Not Seen
			if (SeesPlayer == false) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Player Lost"));
				AIController->SetPlayerLost();
			}
		}
	}

	// Set SeesPlayer = false after interval delay
	sightTimer += GetWorld()->GetDeltaSeconds();
	if (sightTimer > sightDelay) {	// The timer is reset if the player gets seen ('OnPlayerCaught()'), ...
		SeesPlayer = false;			// ... this means that while it is in sight it will never enter the 'if()' condition
	}
	

}

// Called to bind functionality to input
void ANemesisCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANemesisCharacter::OnPlayerCaught(APawn * Pawn)
{
	SeesPlayer = true; // Always at the beginning
	sightTimer = 0.f;  // ...

	ANemesisAIController* AIController = Cast<ANemesisAIController>(GetController());

	if (AIController) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Player Caught"));
		AIController->SetPlayerCaught(Pawn);
	}
}

