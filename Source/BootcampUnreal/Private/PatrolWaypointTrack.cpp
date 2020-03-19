// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolWaypointTrack.h"
#include "BootcampEnemyCharacter.h"

APatrolWaypointTrack::APatrolWaypointTrack()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APatrolWaypointTrack::BeginPlay()
{
	Super::BeginPlay();
    Init();
}

void APatrolWaypointTrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APatrolWaypointTrack::Init()
{
    World = GetWorld();
    WillSpawnEnemy();
}

void APatrolWaypointTrack::WillSpawnEnemy()
{
    World->GetTimerManager().SetTimer(TimerHandle, this, &APatrolWaypointTrack::OnSpawnEnemy, DelayEnemySpawn, false);
}

void APatrolWaypointTrack::OnSpawnEnemy()
{
    if (WayPointPositions.Num() > 0)
    {
        FActorSpawnParameters ActorSpawnParams;
        ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
        ABootcampEnemyCharacter* Enemy = World->SpawnActor<ABootcampEnemyCharacter>(EnemyCharacter,
                                                                                    WayPointPositions[0]->GetActorLocation(),
                                                                                    WayPointPositions[0]->GetActorRotation(),
                                                                                    ActorSpawnParams);
        
        if (Enemy)
        {
            Enemy->SetTrackPoints(WayPointPositions);
            Enemy->OnEnemyDieDelegate.BindUObject(this, &APatrolWaypointTrack::WillSpawnEnemy);
        }
    }
}
