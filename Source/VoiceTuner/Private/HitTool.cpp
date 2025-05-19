// Fill out your copyright notice in the Description page of Project Settings.

/*
 *	Author: Lee Dong Geun
 */

#include "HitTool.h"

#include "MusicNote.h"
#include "PointComponent.h"
#include "VoiceTunerCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

 // Sets default values
AHitTool::AHitTool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	HitCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit Collision"));
	HitCollision->SetupAttachment(RootComponent);
	HitCollision->SetBoxExtent(FVector(50.0f , 50.0f , 50.0f));
	HitCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hit Mesh"));
	HitMesh->SetupAttachment(RootComponent);
	HitMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HitCollision->OnComponentBeginOverlap.AddDynamic(this , &AHitTool::OnNoteOverlap);
}

// Called when the game starts or when spawned
void AHitTool::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AHitTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHitTool::ActivationCollision(bool bIsActivated)
{
	bIsActivated ? HitCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly) : HitCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AHitTool::OnNoteOverlap(UPrimitiveComponent* OverlappedComponent , AActor* OtherActor ,
	UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult)
{
	if ( AMusicNote* MusicNote = Cast<AMusicNote>(OtherActor) )
	{
		if ( AVoiceTunerCharacter* owner = Cast<AVoiceTunerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()) )
		{
			owner->GetPointComponent()->AddPoint(50);
			OnHit();
		}

		if ( HitParticle )
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld() , HitParticle , GetActorLocation());
		}
		UE_LOG(LogTemp , Warning , TEXT("Hit!"));
		MusicNote->Destroy();
	}
}
