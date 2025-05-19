// Fill out your copyright notice in the Description page of Project Settings.

/*
 *	Author: Lee Dong Geun
 */

#include "TrafficLight.h"

#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
ATrafficLight::ATrafficLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComp"));
	SetRootComponent(ArrowComp);

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp -> SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATrafficLight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrafficLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

