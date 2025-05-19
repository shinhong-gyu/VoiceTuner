// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PersonalRoomAudio.generated.h"

UCLASS()
class VOICETUNER_API APersonalRoomAudio : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APersonalRoomAudio();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class ABGMAudioActor* bgmAudio;

	UFUNCTION(BlueprintCallable , Category = "Audio")
	void PlayAudio(int32 gender, int32 octave);

	// Function to stop the audio
	UFUNCTION(BlueprintCallable , Category = "Audio")
	void StopAudio();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABGMAudioActor> BGMAudioFactory;
private:

	UPROPERTY()
	class UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere , Category = "Audio")
	class USoundWave* Octave1;
	UPROPERTY(EditAnywhere , Category = "Audio")
	class USoundWave* ManOctave2;
	UPROPERTY(EditAnywhere , Category = "Audio")
	class USoundWave* ManOctave3;
	UPROPERTY(EditAnywhere , Category = "Audio")
	class USoundWave* WomanOctave2;
	UPROPERTY(EditAnywhere , Category = "Audio")
	class USoundWave* WomanOctave3;


};
