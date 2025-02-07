// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "NemesisPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNEMESIS_API ANemesisPatrolPoint : public ATargetPoint
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Path)
	int32 pathID = 0;

public:
	FORCEINLINE int32 GetPathID() const { return pathID; }
	FORCEINLINE void SetPathID(int32 newID) { pathID = newID; }

};
