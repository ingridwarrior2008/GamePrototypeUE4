// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PatrolInterface.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Engine/TargetPoint.h"
#include "BootcampEnemyCharacter.generated.h"

DECLARE_DELEGATE(FOnEnemyDieDelegate)

class UPawnSensingComponent;
class AEnemyAIController;

UCLASS()
class BOOTCAMPUNREAL_API ABootcampEnemyCharacter : public ACharacter, public IPatrolInterface
{
    GENERATED_BODY()
    
public:
    ABootcampEnemyCharacter();
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
    
    void SetTrackPoints(TArray<ATargetPoint *> TrackPointsArray);
    
    UFUNCTION()
    virtual int GetNextWaypointIndex();
    
    UFUNCTION()
    virtual AActor *GetNextWaypointVector(int Index);
    
    UFUNCTION()
    virtual void SetWaypointVector();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    const float GetHealth() { return Health; }
    
    UFUNCTION(BlueprintImplementableEvent)
    void OnEnemyStateChanged();
    
    UFUNCTION()
    void SetFollowingPlayer(bool FollowPlayer);
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MaxHealth;
    
    UPROPERTY(EditAnywhere)
    UBehaviorTree* BehaviorTree;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    UPawnSensingComponent *PawnSensingComponent;
    
    FOnEnemyDieDelegate OnEnemyDieDelegate;
    
protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
private:
    UFUNCTION()
    void OnPlayerDetected(APawn* Pawn);
    
    UFUNCTION()
    void Init();
    
    UFUNCTION()
    void OnCharacterStateChanged();
    
    UPROPERTY()
    float Health;
    
    UPROPERTY()
    TArray<ATargetPoint *> TrackPoints;
    
    UPROPERTY()
    int CurrentWaypointIndex;
    
    UPROPERTY()
    int bIsFollowingPlayer;
    
    UPROPERTY()
    AEnemyAIController *EnemyAIController;
};
