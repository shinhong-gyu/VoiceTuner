// Fill out your copyright notice in the Description page of Project Settings.


#include "NetTPSPlayerState.h"
#include "HSW_NetGameInstance.h"

void ANetTPSPlayerState::BeginPlay()
{
	Super::BeginPlay();

	auto* pc = GetWorld()->GetFirstPlayerController();

	if ( pc && pc->IsLocalController() ) {
		auto* gi = Cast<UHSW_NetGameInstance>(GetWorld()->GetGameInstance());
		if ( gi ) {
			ServerRPCSetPlayerName(gi->MySessionName);
		}
	}
}


void ANetTPSPlayerState::ServerRPCSetPlayerName_Implementation(const FString& newName)
{
	SetPlayerName(newName);
}
