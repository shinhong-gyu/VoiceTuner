// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResultWIdget.generated.h"

/**
 *
 */
UCLASS()
class VOICETUNER_API UResultWIdget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeoMetry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TB_Score;

	UFUNCTION(BlueprintCallable)
	void SetScore(int32 Score);

	UPROPERTY(meta = (BindWidget))
	class UMultiLineEditableTextBox* TB_FeedBack;

	UPROPERTY(meta=(BindWidget))
	class UButton* Button_ReqAIFeedBack;

	UFUNCTION()
	void OnClickFeedBackButton();
};
