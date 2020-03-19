// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

class UBehaviorTreeComponent;
class ABootcampEnemyCharacter;

UENUM(BlueprintType)
enum class ECharacterEnemyState : uint8
{
    E_Patrol UMETA(DisplayName = "Patrol"),
    E_Follow UMETA(DisplayName = "Follow")
};

DECLARE_DELEGATE(FOnCharacterStateChanged)

/**
 *
 */
UCLASS()
class BOOTCAMPUNREAL_API AEnemyAIController : public AAIController
{
    GENERATED_BODY()
    
public:
    AEnemyAIController();
    
    virtual void OnPossess(APawn* InPawn) override;
    
    UFUNCTION()
    void StartFollow(AActor *Enemy);
    
    UFUNCTION()
    void StartPatrol();
    
    UFUNCTION()
    void SetNexPatrolPoint(AActor *PatrolPoint);
    
    UBlackboardComponent* GetBlackboard();
    
    UPROPERTY(BlueprintReadWrite)
    ECharacterEnemyState EnemyState;
    
    UPROPERTY(EditDefaultsOnly, Category = AI)
    FName CharacterEnemyStateKey;
    
    UPROPERTY(EditDefaultsOnly, Category = AI)
    FName PatrolPointVectorKey;
    
    UPROPERTY(EditDefaultsOnly, Category = AI)
    FName PlayerVectorKey;
    
    FOnCharacterStateChanged OnCharacterStateChangedDelegate;

protected:
    
    UPROPERTY(BlueprintReadWrite)
    UBlackboardComponent* BlackboardComponent;
    
    UPROPERTY(BlueprintReadWrite)
    UBehaviorTreeComponent* BehaviorComponent;
    
private:
    UFUNCTION()
    void EnemyChangeState(ECharacterEnemyState PhaseType);
    
    UPROPERTY()
    ABootcampEnemyCharacter* EnemyCharacter;
};
