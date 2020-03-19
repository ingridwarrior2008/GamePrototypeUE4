// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PatrolInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPatrolInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOOTCAMPUNREAL_API IPatrolInterface
{
	GENERATED_BODY()

public:
    UFUNCTION()
    virtual int GetNextWaypointIndex();
    
    UFUNCTION()
    virtual AActor *GetNextWaypointVector(int Index);
    
    UFUNCTION()
    virtual void SetWaypointVector();
};
