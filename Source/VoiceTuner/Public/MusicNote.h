// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/*
 *	Author: Lee Dong Geun
 */

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MusicNote.generated.h"

class UBoxComponent;

UCLASS()
class VOICETUNER_API AMusicNote : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* NoteCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* NoteMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float Speed = 500.f;
	
public:	
	// Sets default values for this actor's properties
	AMusicNote();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move();
};
