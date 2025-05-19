// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEndAudio.h"
#include "Components/AudioComponent.h"

// Sets default values
AGameEndAudio::AGameEndAudio()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->bAutoActivate = false;
	SetRootComponent(AudioComp);
}

// Called when the game starts or when spawned
void AGameEndAudio::BeginPlay()
{
	Super::BeginPlay();

	AudioComp->SetSound(endGameSVX);
}

// Called every frame
void AGameEndAudio::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameEndAudio::PlayAudio()
{
	if ( AudioComp == nullptr ) return;
	AudioComp->Play();
}

void AGameEndAudio::StopAudio()
{
	if ( AudioComp == nullptr ) return;
	AudioComp->Stop();
}

