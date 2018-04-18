// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal_Out.generated.h"

UCLASS()
class PROJECTNEMESIS_API APortal_Out : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal_Out();

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

	void OnPlayerEnter(UPrimitiveComponent* overlap_primitive, AActor* in_actor, UPrimitiveComponent* in_primitive, int32 body_id, bool bFromSweep, const FHitResult& hit);

	bool player_detected = false;
	
};
