// Fill out your copyright notice in the Description page of Project Settings.

/*
 *	Author: Lee Dong Geun
 */

#include "MusicNote.h"

#include "Components/BoxComponent.h"

// Sets default values
AMusicNote::AMusicNote()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    AActor::SetLifeSpan(3.f);

	NoteCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Note Collision"));
	SetRootComponent(NoteCollision);
	NoteCollision -> SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	NoteMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Note Mesh"));
	NoteMesh -> SetupAttachment(RootComponent);
	NoteMesh -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AMusicNote::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMusicNote::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();
}

void AMusicNote::Move()
{
	FVector NewLocation = GetActorLocation() + Speed * GetActorForwardVector() * GetWorld() -> GetDeltaSeconds();
	SetActorLocation(NewLocation);
}