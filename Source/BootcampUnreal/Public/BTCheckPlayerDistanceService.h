// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTCheckPlayerDistanceService.generated.h"

/**
 *
 */
UCLASS()
class BOOTCAMPUNREAL_API UBTCheckPlayerDistanceService : public UBTService
{
    GENERATED_BODY()
    
protected:
    virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Services, meta = (AllowPrivateAccess = "true"))
    FBlackboardKeySelector PlayerReftActorKey;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Services, meta = (AllowPrivateAccess = "true"))
    float MinDistanceToFollow;
};
