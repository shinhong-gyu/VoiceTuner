// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BGMAudioActor.generated.h"

UCLASS()
class VOICETUNER_API ABGMAudioActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABGMAudioActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UAudioComponent* AudioComp;

	UFUNCTION(BlueprintCallable)
	void PlayAudio();

	UFUNCTION(BlueprintCallable)
	void StopAudio();

	UPROPERTY(EditAnywhere)
	class USoundBase* bgmSVX;
};
