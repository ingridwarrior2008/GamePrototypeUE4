// Fill out your copyright notice in the Description page of Project Settings.


#include "BootCampCharacter.h"

// MARK: - Constructor -

ABootCampCharacter::ABootCampCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

// MARK: - Lifecycle -

void ABootCampCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABootCampCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// MARK: - Public Methods -

void ABootCampCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
