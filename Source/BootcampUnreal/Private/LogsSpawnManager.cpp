// Fill out your copyright notice in the Description page of Project Settings.


#include "LogsSpawnManager.h"

// MARK: - Constructor -

ALogsSpawnManager::ALogsSpawnManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

// MARK: - Lifecycle -

void ALogsSpawnManager::BeginPlay()
{
    Super::BeginPlay();
    Init();
}

void ALogsSpawnManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ALogsSpawnManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

// MARK: - Private methods -

void ALogsSpawnManager::Init()
{
    World = GetWorld();
    
    TimerDelegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ALogsSpawnManager, OnSpawnLogs));
    World->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, LogsTimerInterval, true, LogsDelayStartTime);
}

void ALogsSpawnManager::OnSpawnLogs()
{
    check(LogsActor != nullptr);
    
    for (ATargetPoint *TargetPoint : TargetPoints)
    {
        FActorSpawnParameters ActorSpawnParams;
        ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
        World->SpawnActor<AActor>(LogsActor, TargetPoint->GetActorLocation(), TargetPoint->GetActorRotation(), ActorSpawnParams);
    }
}
