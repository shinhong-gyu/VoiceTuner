// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"

/**
 *
 */
UCLASS()
class VOICETUNER_API UMainUI : public UUserWidget
{
	GENERATED_BODY()

public:
	// 	virtual void NativeOnMouseEnter(const FGeometry& InGeometry , const FPointerEvent& InMouseEvent) override;
	// 	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere , meta = ( BindWidget ))
	class UGridPanel* ICON_GP;

	UPROPERTY(meta = ( BindWidgetAnim ) , Transient)
	class UWidgetAnimation* MouseHover;

	UPROPERTY(EditAnywhere , meta = ( BindWidget ))
	class UButton* HoverZone;
	UPROPERTY(EditAnywhere , meta = ( BindWidget ))
	class UButton* Button_OnOffMic;
	UPROPERTY(EditAnywhere , meta = ( BindWidget ))
	class UButton* Button_Chatting;
	UPROPERTY(EditAnywhere , meta = ( BindWidget ))
	class UButton* Button_Emotion;
	UPROPERTY(EditAnywhere , meta = ( BindWidget ))
	class UButton* Button_Setting;
	UPROPERTY(EditAnywhere , meta = ( BindWidget ))
	class UButton* Button_OnOffSound;
	UPROPERTY(EditAnywhere , meta = ( BindWidget ))
	class UButton* Button_Email;

	
	UPROPERTY(EditAnywhere , meta = ( BindWidget ))
	class UImage* ICON_OnOffSound;
	UPROPERTY(EditAnywhere , meta = ( BindWidget ))
	class UImage* ICON_OnOffMic;
	UPROPERTY(EditAnywhere , meta = ( BindWidget ))
	class UImage* ICON_Chatting;
	UPROPERTY(EditAnywhere , meta = ( BindWidget ))
	class UImage* ICON_Setting;
	UPROPERTY(EditAnywhere , meta = ( BindWidget ))
	class UImage* ICON_Emotion;
	UPROPERTY(EditAnywhere , meta = ( BindWidget ))
	class UImage* ICON_Email;

	UFUNCTION()
	void OnMyHZHoverd();
	UFUNCTION()
	void OnMySoundOnOffButtonClicked();
	UFUNCTION()
	void OnMyMicOnOffButtonClicked();
	UFUNCTION()
	void OnMyEmailHoverd();
	UFUNCTION()
	void OnMyEmtionHoverd();
	UFUNCTION()
	void OnMyOOMHoverd();
	UFUNCTION()
	void OnMyOOSHoverd();
	UFUNCTION()
	void OnMyChatHoverd();
	UFUNCTION()
	void OnMySetHoverd();

	UFUNCTION()
	void OnMyEmailUnHoverd();
	UFUNCTION()
	void OnMyEmtionUnHoverd();
	UFUNCTION()
	void OnMyOOMUnHoverd();
	UFUNCTION()
	void OnMyOOSUnHoverd();
	UFUNCTION()
	void OnMyChatUnHoverd();
	UFUNCTION()
	void OnMySetUnHoverd();

	bool bGPUp = false;

	bool bSoundOff = false;
	bool bMicOff = false;
};

