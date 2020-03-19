// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskEnemyPatrol.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTaskEnemyPatrol::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    EBTNodeResult::Type NodeResult = EBTNodeResult::Failed;
    
    if (AEnemyAIController *AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()))
    {
        if (UBlackboardComponent *BlackboardComponent = OwnerComp.GetBlackboardComponent())
        {
            FVector WaypointLocation = BlackboardComponent->GetValueAsVector(WayPointVectorKey.SelectedKeyName);
            EPathFollowingRequestResult::Type RequestResult = AIController->MoveToLocation(WaypointLocation);
            NodeResult = GetNodeResultByPathFollowing(RequestResult);
        }
    }
    return NodeResult;
}

EBTNodeResult::Type UBTTaskEnemyPatrol::GetNodeResultByPathFollowing(EPathFollowingRequestResult::Type PathFollowingRequestResult)
{
    switch (PathFollowingRequestResult)
    {
        case EPathFollowingRequestResult::AlreadyAtGoal:
            return EBTNodeResult::Succeeded;
        case EPathFollowingRequestResult::RequestSuccessful:
            return EBTNodeResult::InProgress;
        case EPathFollowingRequestResult::Failed:
            return EBTNodeResult::Failed;
    }
    
    return EBTNodeResult::Failed;
}
