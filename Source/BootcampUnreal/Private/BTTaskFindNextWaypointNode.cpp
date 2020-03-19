// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskFindNextWaypointNode.h"
#include "PatrolInterface.h"
#include "AIController.h"

EBTNodeResult::Type UBTTaskFindNextWaypointNode::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    EBTNodeResult::Type NodeResult = EBTNodeResult::Failed;
    
    if (AAIController *EnemyController = OwnerComp.GetAIOwner())
    {
        
        if (IPatrolInterface *PatrolInterface = Cast<IPatrolInterface>(EnemyController->GetPawn()))
        {
            PatrolInterface->SetWaypointVector();
            NodeResult = EBTNodeResult::Succeeded;
        }
    }
    return NodeResult;
}

