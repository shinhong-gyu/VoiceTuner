// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/*
 *	Author: Lee Dong Geun
 */

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrafficLight.generated.h"

class UArrowComponent;

UCLASS()
class VOICETUNER_API ATrafficLight : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Root, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ArrowComp;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = TrafficLight, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* AudioComp;

	
public:	
	// Sets default values for this actor's properties
	ATrafficLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
