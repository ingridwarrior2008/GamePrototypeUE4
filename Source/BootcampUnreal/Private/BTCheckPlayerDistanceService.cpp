// Fill out your copyright notice in the Description page of Project Settings.


#include "BTCheckPlayerDistanceService.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"

void UBTCheckPlayerDistanceService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    AEnemyAIController *EnemyAIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
    UBlackboardComponent *BlackboardComponent = OwnerComp.GetBlackboardComponent();
    APawn *Player = Cast<APawn>(BlackboardComponent->GetValueAsObject(PlayerReftActorKey.SelectedKeyName));
    
    if (EnemyAIController && EnemyAIController->EnemyState == ECharacterEnemyState::E_Follow)
    {
        /*TODO:
         FVector TargetLocation = Player->GetActorLocation();
         FVector EnemyLocation = EnemyAIController->GetPawn()->GetActorLocation();
         FVector DirectionVector = TargetLocation - EnemyLocation;
         float Distance = DirectionVector.Size();
         GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), Distance));
         
         if (Distance > MinDistanceToFollow)
         {
            EnemyAIController->StartPatrol();
         }
         
         */
  
        UPawnSensingComponent* SensingComponent = EnemyAIController->GetPawn()->FindComponentByClass<UPawnSensingComponent>();

        if (!SensingComponent->CouldSeePawn(Player))
        {
            EnemyAIController->StartPatrol();
        }
        
    }
}
