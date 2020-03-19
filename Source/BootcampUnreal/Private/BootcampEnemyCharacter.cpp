// Fill out your copyright notice in the Description page of Project Settings.


#include "BootcampEnemyCharacter.h"
#include "BootCampCharacter.h"
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/PawnSensingComponent.h"

// MARK: - Constructor -

ABootcampEnemyCharacter::ABootcampEnemyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
}

// MARK: - Lifecycle -

void ABootcampEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();
    Init();
}

void ABootcampEnemyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABootcampEnemyCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    OnEnemyDieDelegate.ExecuteIfBound();
}

// MARK: - Public Methods -

void ABootcampEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ABootcampEnemyCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
    
    Health -= Damage;
    
    return Damage;
}

void ABootcampEnemyCharacter::SetTrackPoints(TArray<ATargetPoint *> TrackPointsArray)
{
    CurrentWaypointIndex = 0;
    TrackPoints.Empty();
    TrackPoints = TrackPointsArray;
    
    if (EnemyAIController)
    {
        EnemyAIController->SetNexPatrolPoint(GetNextWaypointVector(0));
    }
}

void ABootcampEnemyCharacter::SetFollowingPlayer(bool FollowPlayer)
{
    bIsFollowingPlayer = FollowPlayer;
}

// MARK: - Interface IPatrol -

int ABootcampEnemyCharacter::GetNextWaypointIndex()
{
    if (TrackPoints.Num() > 0 &&
        CurrentWaypointIndex != TrackPoints.Num() - 1)
    {
        CurrentWaypointIndex++;
    }
    else
    {
        CurrentWaypointIndex = 0;
    }
    
    return CurrentWaypointIndex;
}

AActor *ABootcampEnemyCharacter::GetNextWaypointVector(int Index)
{
    return TrackPoints[Index];
}

void ABootcampEnemyCharacter::SetWaypointVector()
{
    if (EnemyAIController)
    {
        EnemyAIController->SetNexPatrolPoint(GetNextWaypointVector(GetNextWaypointIndex()));
    }
}

// MARK: - Delegates -

void ABootcampEnemyCharacter::OnPlayerDetected(APawn* Pawn)
{
    if (EnemyAIController && !bIsFollowingPlayer)
    {
        TArray<AActor*> Player;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABootCampCharacter::StaticClass(), Player);
        
        if (Player.Num() > 0)
        {
            EnemyAIController->StartFollow(Player[0]);
            bIsFollowingPlayer = true;
        }
    }
}

// MARK: - Private Methods -
void ABootcampEnemyCharacter::Init()
{
    Health = MaxHealth;
    EnemyAIController = Cast<AEnemyAIController>(GetController());
    check(EnemyAIController != nullptr);
    
    EnemyAIController->OnCharacterStateChangedDelegate.BindUObject(this, &ABootcampEnemyCharacter::OnCharacterStateChanged);
    
    if (PawnSensingComponent)
    {
        PawnSensingComponent->OnSeePawn.AddDynamic(this, &ABootcampEnemyCharacter::OnPlayerDetected);
    }
}

void ABootcampEnemyCharacter::OnCharacterStateChanged()
{
    OnEnemyStateChanged();
}

