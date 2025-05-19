// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PersonalRoomWidget.generated.h"

/**
 *
 */
UCLASS()
class VOICETUNER_API UPersonalRoomWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnMy1OctaveButtonClick();
	UFUNCTION()
	void OnMy2OctaveButtonClick();
	UFUNCTION()
	void OnMy3OctaveButtonClick();
	UFUNCTION()
	void OnMyStopButtonClick();
	UFUNCTION()
	void OnMyManKeyButtonClick();
	UFUNCTION()
	void OnMyWomanKeyButtonClick();

	UFUNCTION()
	void OnClicked1OctaveButton();
	UFUNCTION()
	void OnClicked2OctaveButton();
	UFUNCTION()
	void OnClicked3OctaveButton();
	UFUNCTION()
	void OnClickRepeat();
	UFUNCTION()
	void OnClickScale();

	UPROPERTY(BlueprintReadWrite , meta = ( BindWidget ))
	class UButton* PlayButton_1Octave;

	UPROPERTY(BlueprintReadWrite , meta = ( BindWidget ))
	class UButton* PlayButton_2Octave;

	UPROPERTY(BlueprintReadWrite , meta = ( BindWidget ))
	class UButton* PlayButton_3Octave;

	UPROPERTY(BlueprintReadWrite , meta = ( BindWidget ))
	class UButton* PauseButton_1Octave;

	UPROPERTY(BlueprintReadWrite , meta = ( BindWidget ))
	class UButton* PauseButton_2Octave;

	UPROPERTY(BlueprintReadWrite , meta = ( BindWidget ))
	class UButton* PauseButton_3Octave;


	
	UPROPERTY(BlueprintReadWrite , meta = ( BindWidget ))
	class UButton* Button_1Octave;
	
	UPROPERTY(BlueprintReadWrite , meta = ( BindWidget ))
	class UButton* Button_2Octave;
	
	UPROPERTY(BlueprintReadWrite , meta = ( BindWidget ))
	class UButton* Button_3Octave;

	class UButton* PreClickedButton;

	UPROPERTY(BlueprintReadWrite , meta = ( BindWidget ))
	class UButton* Button_Man;

	UPROPERTY(BlueprintReadWrite , meta = ( BindWidget ))
	class UButton* Button_Woman;

	UPROPERTY(BlueprintReadWrite , meta = ( BindWidget ))
	class UButton* Button_Repeat;
	UPROPERTY(BlueprintReadWrite , meta = ( BindWidget ))
	class UButton* Button_Scale; 

	UPROPERTY(BlueprintReadWrite , meta = ( BindWidget ))
	class UButton* Button_Back;

	UFUNCTION()
	void OnCancelButtonClick();

	int32 genderCode;

	int32 selected;

	bool bIs1Clicked = false;
	bool bIs2Clicked = false;
	bool bIs3Clicked = false;

	bool bIsMKClicked = false;
	bool bIsWKClicked = false;

	bool bIsRClicked = false;
	bool bIsSClicked = false;
	bool bIsAClicked = false;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APersonalRoomAudio> PRAFactory;

	class APersonalRoomAudio* audioActor;

	FSlateBrush NewBrush;
};
