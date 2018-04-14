// Fill out your copyright notice in the Description page of Project Settings.

#include "Talisman.h"
#include "Runtime/Engine/Classes/Components/MeshComponent.h"
#include "Runtime/Engine/Classes/Components/ShapeComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"

// Sets default values
ATalisman::ATalisman()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = root;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("test_mesh"));
	mesh->AttachToComponent(root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
	shape = CreateDefaultSubobject<UBoxComponent>(TEXT("test_shape"));
	shape->bGenerateOverlapEvents = true;
	shape->SetWorldScale3D(FVector(1.0f,1.0f,1.0f));

// ATalisman overlap
	shape->OnComponentBeginOverlap.AddDynamic(this, &ATalisman::OnPedestalEnter);
	shape->AttachToComponent(root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
// Material
	current_mat = mesh->CreateDynamicMaterialInstance(0);
}

// Called when the game starts or when spawned
void ATalisman::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATalisman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	if (changed_color == true && current_mat != nullptr)
	{
		current_mat->SetScalarParameterValue(FName("ColorAmount"), 1.0f);
	}

}

void ATalisman::OnPedestalEnter(UPrimitiveComponent * overlap_primitive, AActor * in_actor, UPrimitiveComponent * in_primitive, int32 body_id, bool bFromSweep, const FHitResult & hit)
{
	//if (in_actor->ActorHasTag(FName("Pedestal")) == true)
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Screen Message"));
		changed_color = true;
}
