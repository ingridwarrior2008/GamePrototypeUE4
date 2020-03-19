// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICraftable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UICraftable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOOTCAMPUNREAL_API IICraftable
{
	GENERATED_BODY()
public:
    
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void CraftWood(int Quantity);
};
