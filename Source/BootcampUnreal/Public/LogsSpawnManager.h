// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TargetPoint.h"
#include "LogsSpawnManager.generated.h"


UCLASS()
class BOOTCAMPUNREAL_API ALogsSpawnManager : public AActor
{
    GENERATED_BODY()
    
public:
    ALogsSpawnManager();
    virtual void Tick(float DeltaTime) override;
    
    UPROPERTY(EditDefaultsOnly, Category=LogsSpawn)
    TSubclassOf<class AActor> LogsActor;
    
    UPROPERTY(EditAnywhere, Category = LogsSpawn)
    TArray<ATargetPoint *> TargetPoints;
    
protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
    
private:
    
    UFUNCTION()
    void OnSpawnLogs();
    
    UFUNCTION()
    void Init();
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    float LogsDelayStartTime;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    float LogsTimerInterval;
    
    UPROPERTY()
    UWorld *World;
    
    FTimerDelegate TimerDelegate;
    FTimerHandle TimerHandle;
};
