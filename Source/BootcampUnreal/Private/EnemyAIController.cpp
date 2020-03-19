// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BootcampEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

AEnemyAIController::AEnemyAIController()
{
    BehaviorComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComponent"));
    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
    EnemyState = ECharacterEnemyState::E_Patrol;
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    EnemyCharacter = Cast<ABootcampEnemyCharacter>(InPawn);
    if (EnemyCharacter)
    {
        BlackboardComponent->InitializeBlackboard(*(EnemyCharacter->BehaviorTree->BlackboardAsset));
        BehaviorComponent->StartTree(*(EnemyCharacter->BehaviorTree));
        StartPatrol();
    }
}

UBlackboardComponent* AEnemyAIController::GetBlackboard()
{
    return  BlackboardComponent;
}

void AEnemyAIController::StartFollow(AActor *Enemy)
{
    BlackboardComponent->SetValueAsObject(PlayerVectorKey, Enemy);
    EnemyChangeState(ECharacterEnemyState::E_Follow);
}

void AEnemyAIController::StartPatrol()
{
    EnemyCharacter->SetFollowingPlayer(false);
    BlackboardComponent->ClearValue(PlayerVectorKey);
    EnemyChangeState(ECharacterEnemyState::E_Patrol);
}

void AEnemyAIController::SetNexPatrolPoint(AActor *PatrolPoint)
{
    BlackboardComponent->SetValueAsObject(PatrolPointVectorKey, PatrolPoint);
}

// MARK: - Private Methods -

void AEnemyAIController::EnemyChangeState(ECharacterEnemyState PhaseType)
{
    EnemyState = PhaseType;
    BlackboardComponent->SetValueAsEnum(CharacterEnemyStateKey, (uint8)EnemyState);
    OnCharacterStateChangedDelegate.ExecuteIfBound();
}
