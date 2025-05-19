// Fill out your copyright notice in the Description page of Project Settings.


#include "PersonalRoomAudio.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWave.h"
#include "BGMAudioActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APersonalRoomAudio::APersonalRoomAudio()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->bAutoActivate = false;
	SetRootComponent(AudioComp);

	ConstructorHelpers::FObjectFinder<USoundWave> TempSoundWave1(TEXT("/Script/Engine.SoundWave'/Game/SHK/resource/Sound/MAN_C1_Practice_WOMAN_C0_Practice.MAN_C1_Practice_WOMAN_C0_Practice'"));
	if ( TempSoundWave1.Succeeded() ) {
		Octave1 = TempSoundWave1.Object;
	}
	ConstructorHelpers::FObjectFinder<USoundWave> TempSoundWave2(TEXT("/Script/Engine.SoundWave'/Game/SHK/resource/Sound/MAN_C2_Practice.MAN_C2_Practice'"));
	if ( TempSoundWave1.Succeeded() ) {
		ManOctave2 = TempSoundWave2.Object;
	}
	ConstructorHelpers::FObjectFinder<USoundWave> TempSoundWave3(TEXT("/Script/Engine.SoundWave'/Game/SHK/resource/Sound/MAN_C3_Practice.MAN_C3_Practice'"));
	if ( TempSoundWave1.Succeeded() ) {
		ManOctave3 = TempSoundWave3.Object;
	}
	ConstructorHelpers::FObjectFinder<USoundWave> TempSoundWave4(TEXT("/Script/Engine.SoundWave'/Game/SHK/resource/Sound/WOMAN_C1_Practice.WOMAN_C1_Practice'"));
	if ( TempSoundWave1.Succeeded() ) {
		WomanOctave2 = TempSoundWave4.Object;
	}
	ConstructorHelpers::FObjectFinder<USoundWave> TempSoundWave5(TEXT("/Script/Engine.SoundWave'/Game/SHK/resource/Sound/WOMAN_C2_Practice.WOMAN_C2_Practice'"));
	if ( TempSoundWave1.Succeeded() ) {
		WomanOctave3 = TempSoundWave5.Object;
	}
	bgmAudio = Cast<ABGMAudioActor>(UGameplayStatics::GetActorOfClass(GetWorld() , BGMAudioFactory));
}

// Called when the game starts or when spawned
void APersonalRoomAudio::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APersonalRoomAudio::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APersonalRoomAudio::PlayAudio(int32 gender , int32 octave)
{
	if ( bgmAudio != nullptr ) {
		bgmAudio->StopAudio();
	}

	if ( AudioComp == nullptr ) return;

	if ( octave == 1 && Octave1 ) {
		AudioComp->SetSound(Octave1);
		AudioComp->Play();
	}
	else {
		if ( gender == 1 ) {
			if ( octave == 2 ) {
				AudioComp->SetSound(ManOctave2);
				AudioComp->Play();
			}
			else {
				AudioComp->SetSound(ManOctave3);
				AudioComp->Play();
			}
		}
		else {
			if ( octave == 2 ) {
				AudioComp->SetSound(WomanOctave2);
				AudioComp->Play();
			}
			else {
				AudioComp->SetSound(WomanOctave3);
				AudioComp->Play();
			}
		}
	}
}

void APersonalRoomAudio::StopAudio()
{
	if ( AudioComp && AudioComp->IsPlaying() )
	{
		if ( bgmAudio != nullptr ) bgmAudio->PlayAudio();

		AudioComp->Stop();
	}
}

