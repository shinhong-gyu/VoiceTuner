// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionSlotWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "HSW_NetGameInstance.h"

void USessionSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Join->OnClicked.AddDynamic(this , &USessionSlotWidget::OnClickJoin);
}

void USessionSlotWidget::OnClickJoin()
{
	// SessionSearchIndex
	auto* gi = Cast<UHSW_NetGameInstance>(GetWorld()->GetGameInstance());
	if ( gi )
	{
		gi->JoinSession(SessionSearchIndex);
		
	}
}

void USessionSlotWidget::UpdateInfo(const struct FRoomInfo& info)
{
	Text_RoomName->SetText(FText::FromString(info.roomName));
	Text_HostName->SetText(FText::FromString(info.hostName));
	FString count = FString::Printf(TEXT("%d / %d") , info.currentPlayerCount , info.maxPlayerCount);
	Text_PlayerCount->SetText(FText::FromString(count));
	Text_PingMS->SetText(FText::AsNumber(info.pingMS));

	SessionSearchIndex = info.index;
}
