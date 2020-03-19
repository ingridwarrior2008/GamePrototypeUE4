// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TargetPoint.h"
#include "PatrolWaypointTrack.generated.h"

class ABootcampEnemyCharacter;

UCLASS()
class BOOTCAMPUNREAL_API APatrolWaypointTrack : public AActor
{
    GENERATED_BODY()
    
public:	
    
    APatrolWaypointTrack();
    virtual void Tick(float DeltaTime) override;
    
    
    UPROPERTY(EditDefaultsOnly, Category = PatrolWayPoint)
    TSubclassOf<ABootcampEnemyCharacter> EnemyCharacter;
    
    UPROPERTY(EditAnywhere, Category = PatrolWayPoint)
    TArray<ATargetPoint *> WayPointPositions;
    
    UFUNCTION()
    TArray<ATargetPoint *> GetWayPoints() const { return  WayPointPositions; }

    UFUNCTION()
    void OnSpawnEnemy();
    
protected:
    virtual void BeginPlay() override;
    
private:

    
    UFUNCTION()
    void WillSpawnEnemy();
    
    UFUNCTION()
    void Init();
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    float DelayEnemySpawn;
    
    UPROPERTY()
    UWorld *World;
    
    FTimerHandle TimerHandle;
};
