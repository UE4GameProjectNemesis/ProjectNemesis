// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Talisman.generated.h"

enum TalismanColor { None = 0, Purple, Orange, Unkown };

UCLASS()
class PROJECTNEMESIS_API ATalisman : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATalisman();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		USceneComponent* root;
	
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere)
		UShapeComponent* shape;
	UFUNCTION()
		void OnPedestalEnter(UPrimitiveComponent* overlap_primitive, AActor* in_actor, UPrimitiveComponent* in_primitive, int32 body_id, bool bFromSweep, const FHitResult& hit);


	// --- TALISMAN PROPERTIES ----
	TalismanColor color = None;
	bool changed_color = false;

	UPROPERTY(EditAnywhere)
	UMaterialInstanceDynamic* current_mat;
};
