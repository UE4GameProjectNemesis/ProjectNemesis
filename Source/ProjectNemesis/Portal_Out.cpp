// Fill out your copyright notice in the Description page of Project Settings.

#include "Portal_Out.h"
#include "Engine.h"
#include "Runtime/Engine/Classes/Components/MeshComponent.h"
#include "Runtime/Engine/Classes/Components/ShapeComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"

// Sets default values
APortal_Out::APortal_Out()
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
	shape->OnComponentBeginOverlap.AddDynamic(this, &APortal_Out::OnPlayerEnter);
	shape->AttachToComponent(root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called when the game starts or when spawned
void APortal_Out::BeginPlay()
{
	Super::BeginPlay();

	if (player_detected == true)
	{
		player_detected = false;
	}

}

// Called every frame
void APortal_Out::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortal_Out::OnPlayerEnter(UPrimitiveComponent * overlap_primitive, AActor * in_actor, UPrimitiveComponent * in_primitive, int32 body_id, bool bFromSweep, const FHitResult & hit)
{
	if (in_actor->ActorHasTag(FName("Player")) == true && player_detected == false) {
		player_detected = true;
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::White, TEXT("CONTACT"));
		TArray<AActor*> actors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Portal_In"), actors);

		if (actors.Num() > 0)
		{
			FVector vec = actors[0]->GetActorLocation();
			vec.Z += 12;
			FRotator rot = actors[0]->GetActorRotation();
			
			rot.Yaw -= 180;

			in_actor->SetActorLocationAndRotation(vec, rot);
		}
	}
}

