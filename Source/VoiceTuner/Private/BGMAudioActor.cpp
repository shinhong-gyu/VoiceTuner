// Fill out your copyright notice in the Description page of Project Settings.


#include "BGMAudioActor.h"
#include "Components/AudioComponent.h"

// Sets default values
ABGMAudioActor::ABGMAudioActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->bAutoActivate = false;
	SetRootComponent(AudioComp);
}

// Called when the game starts or when spawned
void ABGMAudioActor::BeginPlay()
{
	Super::BeginPlay();

	AudioComp->SetSound(bgmSVX);
	PlayAudio();
}

// Called every frame
void ABGMAudioActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABGMAudioActor::PlayAudio()
{
	if ( AudioComp == nullptr ) return;
	AudioComp->Play();
}

void ABGMAudioActor::StopAudio()
{
	if ( AudioComp == nullptr ) return;
	AudioComp->Stop();
}

