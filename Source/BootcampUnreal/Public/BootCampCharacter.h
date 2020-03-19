// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BootCampCharacter.generated.h"

UCLASS()
class BOOTCAMPUNREAL_API ABootCampCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABootCampCharacter();
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int CurrentLogs;
    
protected:
	virtual void BeginPlay() override;
};
