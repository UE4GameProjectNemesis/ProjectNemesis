// Fill out your copyright notice in the Description page of Project Settings.

#include "Nemesis.h"
#include "Runtime/Engine/Classes/Components/MeshComponent.h"
#include "Runtime/Engine/Classes/Components/ShapeComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"

// Sets default values
ANemesis::ANemesis()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = root;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("test_mesh"));
	mesh->AttachToComponent(root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	shape = CreateDefaultSubobject<UBoxComponent>(TEXT("test_shape"));
	shape->SetWorldScale3D(FVector(1.0f,1.0f,1.0f));
	shape->bGenerateOverlapEvents = true;
	shape->OnComponentBeginOverlap.AddDynamic(this, &ANemesis::OnPlayer);
	shape->AttachToComponent(root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called when the game starts or when spawned
void ANemesis::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANemesis::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANemesis::OnPlayer(UPrimitiveComponent * overlap_primitive, AActor * in_actor, UPrimitiveComponent * in_primitive, int32 body_id, bool bFromSweep, const FHitResult & hit)
{
	return;
}

