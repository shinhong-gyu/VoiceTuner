// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/*
 *	Author: Lee Dong Geun
 */

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HitTool.generated.h"

class UBoxComponent;

UCLASS()
class VOICETUNER_API AHitTool : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Root, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* HitCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* HitMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Particle, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* HitParticle;
	
public:	
	// Sets default values for this actor's properties
	AHitTool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ActivationCollision(bool bIsActivated);

	UFUNCTION(BlueprintImplementableEvent)
	void OnHit();

	UFUNCTION()
	void OnNoteOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
