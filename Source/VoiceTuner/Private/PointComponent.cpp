// Fill out your copyright notice in the Description page of Project Settings.


#include "PointComponent.h"

// Sets default values for this component's properties
UPointComponent::UPointComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	// ...
}


// Called when the game starts
void UPointComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPointComponent::AddPoint(int Value)
{
	Point += Value;
}

