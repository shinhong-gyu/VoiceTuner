// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"
#include "Components/Button.h"
#include "Animation/WidgetAnimation.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Components/TextBlock.h"
#include "LoginGameMode.h"

void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();
	HoverZone->OnHovered.AddDynamic(this , &UMainUI::OnMyHZHoverd);

	Button_OnOffSound->OnHovered.AddDynamic(this , &UMainUI::OnMyOOSHoverd);
	Button_OnOffMic->OnHovered.AddDynamic(this , &UMainUI::OnMyOOMHoverd);
	Button_Chatting->OnHovered.AddDynamic(this , &UMainUI::OnMyChatHoverd);
	Button_Setting->OnHovered.AddDynamic(this , &UMainUI::OnMySetHoverd);
	Button_Emotion->OnHovered.AddDynamic(this , &UMainUI::OnMyEmtionHoverd);
	Button_Email->OnHovered.AddDynamic(this , &UMainUI::OnMyEmailHoverd);

	Button_OnOffSound->OnUnhovered.AddDynamic(this , &UMainUI::OnMyOOSUnHoverd);
	Button_OnOffMic->OnUnhovered.AddDynamic(this , &UMainUI::OnMyOOMUnHoverd);
	Button_Chatting->OnUnhovered.AddDynamic(this , &UMainUI::OnMyChatUnHoverd);
	Button_Setting->OnUnhovered.AddDynamic(this , &UMainUI::OnMySetUnHoverd);
	Button_Emotion->OnUnhovered.AddDynamic(this , &UMainUI::OnMyEmtionUnHoverd);
	Button_Email->OnUnhovered.AddDynamic(this , &UMainUI::OnMyEmailUnHoverd);

	Button_OnOffSound->OnClicked.AddDynamic(this , &UMainUI::OnMySoundOnOffButtonClicked);
	Button_OnOffMic->OnClicked.AddDynamic(this , &UMainUI::OnMyMicOnOffButtonClicked);
}

void UMainUI::OnMyHZHoverd()
{
	auto* gm = Cast<ALoginGameMode>(GetWorld()->GetAuthGameMode());
	if ( gm ) return;
	if ( MouseHover && !bGPUp ) {
		PlayAnimation(MouseHover);
		bGPUp = true;
	}
}

void UMainUI::OnMySoundOnOffButtonClicked()
{
	if ( !bSoundOff ) {
		bSoundOff = true;
		UTexture2D* SoundOffImg = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/SoundOff.SoundOff'"));
		ICON_OnOffSound->SetBrushFromTexture(SoundOffImg);
	}
	else {
		bSoundOff = false;
		UTexture2D* SoundOnImg = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/YHJ/LOGIN/GUI002v/BASIC/Group_13.Group_13'"));
		ICON_OnOffSound->SetBrushFromTexture(SoundOnImg);
	}
}

void UMainUI::OnMyMicOnOffButtonClicked()
{
	if ( !bMicOff ) {
		bMicOff = true;
		UTexture2D* MicOffImg = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/MicOff.MicOff'"));
		ICON_OnOffMic->SetBrushFromTexture(MicOffImg);
	}
	else {
		bMicOff = false;
		UTexture2D* MicOnImg = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/YHJ/LOGIN/GUI002v/BASIC/Group_14.Group_14'"));
		ICON_OnOffMic->SetBrushFromTexture(MicOnImg);
	}
}

void UMainUI::OnMyEmailHoverd()
{
	UTexture2D* HoverEmailImg = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/YHJ/LOGIN/GUI003v/HOVER/Group_15.Group_15'"));
	ICON_Email->SetBrushFromTexture(HoverEmailImg);
}

void UMainUI::OnMyEmtionHoverd()
{
	UTexture2D* HoverEmotionImg = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/YHJ/LOGIN/GUI003v/HOVER/Group_16.Group_16'"));
	ICON_Emotion->SetBrushFromTexture(HoverEmotionImg);
}

void UMainUI::OnMyOOMHoverd()
{
	if ( !bMicOff ) {
		UTexture2D* HoverOOMImg = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/YHJ/LOGIN/GUI003v/HOVER/Group_14.Group_14'"));
		ICON_OnOffMic->SetBrushFromTexture(HoverOOMImg);
	}
}

void UMainUI::OnMyOOSHoverd()
{
	if ( !bSoundOff ) {
		UTexture2D* HoverOOSImg = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/YHJ/LOGIN/GUI003v/HOVER/Group_13.Group_13'"));
		ICON_OnOffSound->SetBrushFromTexture(HoverOOSImg);
	}
}

void UMainUI::OnMyChatHoverd()
{
	UTexture2D* HoverChatImg = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/YHJ/LOGIN/GUI003v/HOVER/Group_18.Group_18'"));
	ICON_Chatting->SetBrushFromTexture(HoverChatImg);
}

void UMainUI::OnMySetHoverd()
{
	UTexture2D* HoverSetImg = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/YHJ/LOGIN/GUI003v/HOVER/Group_17.Group_17'"));
	ICON_Setting->SetBrushFromTexture(HoverSetImg);
}

void UMainUI::OnMyEmailUnHoverd()
{
	if ( MouseHover ) {
		bGPUp = false;
		PlayAnimation(MouseHover , 0 , 1 , EUMGSequencePlayMode::Reverse);
	}
	UTexture2D* HoverEmailImg = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/YHJ/LOGIN/GUI002v/Basic/Group_15.Group_15'"));
	ICON_Email->SetBrushFromTexture(HoverEmailImg);
}

void UMainUI::OnMyEmtionUnHoverd()
{
	if ( MouseHover ) {
		bGPUp = false;
		PlayAnimation(MouseHover , 0 , 1 , EUMGSequencePlayMode::Reverse);
	}
	UTexture2D* HoverEmotionImg = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/YHJ/LOGIN/GUI002v/Basic/Group_16.Group_16'"));
	ICON_Emotion->SetBrushFromTexture(HoverEmotionImg);
}

void UMainUI::OnMyOOMUnHoverd()
{
	if ( MouseHover ) {
		bGPUp = false;
		PlayAnimation(MouseHover , 0 , 1 , EUMGSequencePlayMode::Reverse);
	}
	if ( !bMicOff ) {
		UTexture2D* HoverOOMImg = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/YHJ/LOGIN/GUI002v/Basic/Group_14.Group_14'"));
		ICON_OnOffMic->SetBrushFromTexture(HoverOOMImg);
	}
}

void UMainUI::OnMyOOSUnHoverd()
{
	if ( MouseHover ) {
		bGPUp = false;
		PlayAnimation(MouseHover , 0 , 1 , EUMGSequencePlayMode::Reverse);
	}
	if ( !bSoundOff ) {
		UTexture2D* HoverOOSImg = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/YHJ/LOGIN/GUI002v/Basic/Group_13.Group_13'"));
		ICON_OnOffSound->SetBrushFromTexture(HoverOOSImg);
	}

}

void UMainUI::OnMyChatUnHoverd()
{
	if ( MouseHover ) {
		bGPUp = false;
		PlayAnimation(MouseHover , 0 , 1 , EUMGSequencePlayMode::Reverse);
	}
	UTexture2D* HoverChatImg = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/YHJ/LOGIN/GUI002v/Basic/Group_18.Group_18'"));
	ICON_Chatting->SetBrushFromTexture(HoverChatImg);
}

void UMainUI::OnMySetUnHoverd()
{
	if ( MouseHover ) {
		bGPUp = false;
		PlayAnimation(MouseHover , 0 , 1 , EUMGSequencePlayMode::Reverse);
	}
	UTexture2D* HoverSetImg = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/YHJ/LOGIN/GUI002v/Basic/Group_17.Group_17'"));
	ICON_Setting->SetBrushFromTexture(HoverSetImg);
}


