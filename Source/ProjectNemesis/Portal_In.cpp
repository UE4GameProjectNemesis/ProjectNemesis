// Fill out your copyright notice in the Description page of Project Settings.

#include "Portal_In.h"
#include "Engine.h"
#include "Runtime/Engine/Classes/Components/MeshComponent.h"
#include "Runtime/Engine/Classes/Components/ShapeComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"

// Sets default values
APortal_In::APortal_In()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = root;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("test_mesh"));
	mesh->AttachToComponent(root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	shape = CreateDefaultSubobject<UBoxComponent>(TEXT("test_shape"));
	shape->bGenerateOverlapEvents = true;
	shape->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));

	// ATalisman overlap
	shape->OnComponentBeginOverlap.AddDynamic(this, &APortal_In::OnPlayerEnter);
	shape->AttachToComponent(root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called when the game starts or when spawned
void APortal_In::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APortal_In::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> actors, play_actors;

	if (player_detected == true)
	{
		player_detected = false;
		switch (color)
		{
		case ETalismanColor::NONE:
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::White, TEXT("Talisman is White"));
			break;
		case ETalismanColor::PURPLE:
			
			UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Portal_Purple"), actors);
			if (actors.Num() > 0)
			{
				UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Player"), actors);
				//play_actors[0]->SetActorLo
				//play_actors[0]->SetActorLocationAndRotation(actors[0]->GetActorLocation(), actors[0]->GetActorRotation());

			}
			break;
		case ETalismanColor::ORANGE:
			UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Portal_Orange"), actors);
			if (actors.Num() > 0)
			{
				UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Player"), actors);
				//play_actors[0]->SetActorLocationAndRotation(actors[0]->GetActorLocation(), actors[0]->GetActorRotation());
			}
			break;
		}
	}

}

void APortal_In::OnPlayerEnter(UPrimitiveComponent * overlap_primitive, AActor * in_actor, UPrimitiveComponent * in_primitive, int32 body_id, bool bFromSweep, const FHitResult & hit)
{
	if (in_actor->ActorHasTag(FName("Player")) == true && player_detected == false) {
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Player Detected"));
		TArray<AActor*> actors;
		in_actor->GetAttachedActors(actors);
		if (actors.Num() > 0)
		{
			for (int8 i = 0; i < actors.Num(); ++i)
			{
				if (actors[i]->ActorHasTag(FName("Talisman")) == true) {
					ATalisman* talisman = Cast<ATalisman>(actors[i]);
					color = talisman->ATalisman::GetTalismanColor();
					player_detected = true;
				}
			}
		}
	}
}
