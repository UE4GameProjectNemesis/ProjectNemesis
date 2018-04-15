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
}

// Called when the game starts or when spawned
void ATalisman::BeginPlay()
{
	Super::BeginPlay();
	// Material

	current_mat = mesh->CreateDynamicMaterialInstance(0);

}

// Called every frame
void ATalisman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	if (changed_color == true && current_mat != nullptr)
	{
		switch (color)
		{
		case ETalismanColor::NONE:
			current_mat->SetScalarParameterValue(FName("Purple_Mat"), 1.0f);
			current_mat->SetScalarParameterValue(FName("Orange_Mat"), 1.0f);
			break;
		case ETalismanColor::PURPLE:
			current_mat->SetScalarParameterValue(FName("Purple_Mat"), 0.0f);
			current_mat->SetScalarParameterValue(FName("Orange_Mat"), 1.0f);
			break;
		case ETalismanColor::ORANGE:
			current_mat->SetScalarParameterValue(FName("Purple_Mat"), 1.0f);
			current_mat->SetScalarParameterValue(FName("Orange_Mat"), 0.0f);
			break;
		}
	}

}

void ATalisman::OnPedestalEnter(UPrimitiveComponent * overlap_primitive, AActor * in_actor, UPrimitiveComponent * in_primitive, int32 body_id, bool bFromSweep, const FHitResult & hit)
{
	if (in_actor->ActorHasTag(FName("Pedestal_Purple")) == true) {
		changed_color = true;
		color = ETalismanColor::PURPLE;
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Purple, TEXT("Talisman is now Purple"));
	}
	else if (in_actor->ActorHasTag(FName("Pedestal_Orange")) == true) {
		changed_color = true;
		color = ETalismanColor::ORANGE;
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, TEXT("Talisman is now Orange"));
	}
}

ETalismanColor ATalisman::GetTalismanColor() const
{
	return color;
}
