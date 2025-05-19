// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PointComponent.generated.h"


UCLASS(Blueprintable , ClassGroup = ( Custom ) , meta = ( BlueprintSpawnableComponent ))
class VOICETUNER_API UPointComponent : public UActorComponent
{
	GENERATED_BODY()

	int Point = 0;

public:
	// Sets default values for this component's properties
	UPointComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetPoint() const { return Point; }

	FORCEINLINE void SetPoint(int NewPoint) { Point = NewPoint; }

	UFUNCTION(BlueprintCallable)
	void AddPoint(int Value);
};
