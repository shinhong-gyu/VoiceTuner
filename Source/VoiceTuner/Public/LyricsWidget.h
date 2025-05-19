// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerState.h"
#include "LyricsWidget.generated.h"

/**
 *
 */
UCLASS()
class VOICETUNER_API ULyricsWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeTick(const FGeometry& MyGeometry , float InDeltaTime) override;
	UPROPERTY(meta = ( BindWidget ))
	class UTextBlock* TB_Score;

	int32 point;

};
