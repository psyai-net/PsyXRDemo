// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/PsyA2FManager.h"


// Sets default values
APsyA2FManager::APsyA2FManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APsyA2FManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APsyA2FManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

