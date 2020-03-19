// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Navigation/PathFollowingComponent.h"
#include "BTTaskEnemyPatrol.generated.h"

/**
 * 
 */
UCLASS()
class BOOTCAMPUNREAL_API UBTTaskEnemyPatrol : public UBTTaskNode
{
	GENERATED_BODY()
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TaskFollowPlayer|Properties", meta = (AllowPrivateAccess = "true"))
    FBlackboardKeySelector WayPointVectorKey;
    
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory);
    EBTNodeResult::Type GetNodeResultByPathFollowing(EPathFollowingRequestResult::Type PathFollowingRequestResult);
};
