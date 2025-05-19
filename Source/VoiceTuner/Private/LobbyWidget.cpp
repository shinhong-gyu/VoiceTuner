// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "HSW_NetGameInstance.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "SessionSlotWidget.h"
#include "Components/ScrollBox.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// �����ν��Ͻ��� �����ͼ�
	auto* gi = Cast<UHSW_NetGameInstance>(GetWorld()->GetGameInstance());
	// OnSearchSignatureCompleteDelegate�� AddSessionSlotWidget�� �����ϰ�ʹ�.
	gi->OnSearchSignatureCompleteDelegate.AddDynamic(this , &ULobbyWidget::AddSessionSlotWidget);

	// �޴� ��ư
	MENU_Button_GoCreateRoom->OnClicked.AddDynamic(this, &ULobbyWidget::MENU_OnClickGoCreateRoom);
	MENU_Button_GoFindSessions->OnClicked.AddDynamic(this, &ULobbyWidget::MENU_OnClickGoFindSessions);

	// �޴��� ���ư��� ��ư��
	CR_Button_GoMenu->OnClicked.AddDynamic(this, &ULobbyWidget::OnClickGoMenu);
	FS_Button_GoMenu->OnClicked.AddDynamic(this , &ULobbyWidget::OnClickGoMenu);

	// �游��� ��ư
	CR_Button_CreateRoom->OnClicked.AddDynamic(this , &ULobbyWidget::CR_OnClickCreateRoom);
	CR_Slider_PlayerCount->OnValueChanged.AddDynamic(this , &ULobbyWidget::CR_OnChangeSliderPlayerCount);

	// ���� ã��
	FS_Button_FindSessions->OnClicked.AddDynamic(this, &ULobbyWidget::FS_OnClickFindSessions);

	CR_Slider_PlayerCount->SetValue(2);
}

void ULobbyWidget::OnClickGoMenu()
{
	LobbyWidgetSwitcher->SetActiveWidgetIndex(0);
}

void ULobbyWidget::MENU_OnClickGoCreateRoom()
{
	LobbyWidgetSwitcher->SetActiveWidgetIndex(1);
}

void ULobbyWidget::MENU_OnClickGoFindSessions()
{
	LobbyWidgetSwitcher->SetActiveWidgetIndex(2);
}

void ULobbyWidget::CR_OnClickCreateRoom()
{
	auto* gi = Cast<UHSW_NetGameInstance>(GetWorld()->GetGameInstance());
	FString roomName = CR_EditText_RoomName->GetText().ToString();

	roomName = roomName.TrimStartAndEnd();
	if ( roomName.IsEmpty() )
	{
		return;
	}
	
	int32 count = ( int32)CR_Slider_PlayerCount->GetValue();
	gi->CreateMySession(roomName, count);
	
}

void ULobbyWidget::CR_OnChangeSliderPlayerCount(float value)
{
	CR_Text_PlayerCount->SetText(FText::AsNumber((int32)value));
}

void ULobbyWidget::FS_OnClickFindSessions()
{
	// ������ �� ����� �����ϰ�
	FS_ScrollBox->ClearChildren();

	// ��ã�⸦ ��û�ϰ�ʹ�.
	auto* gi = Cast<UHSW_NetGameInstance>(GetWorld()->GetGameInstance());
	if ( gi )
	{
		gi->FindOtherSessions();
	}
}

void ULobbyWidget::AddSessionSlotWidget(const struct FRoomInfo& info)
{
	auto* slot = CreateWidget<USessionSlotWidget>(this, SessionSlotWidgetFactory);

	slot->UpdateInfo(info);

	FS_ScrollBox->AddChild(slot);
}
