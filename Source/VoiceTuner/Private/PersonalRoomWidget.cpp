// Fill out your copyright notice in the Description page of Project Settings.


#include "PersonalRoomWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "PersonalRoomAudio.h"
#include "Engine/Texture2D.h"
#include "Styling/SlateBrush.h"
#include "BGMAudioActor.h"

void UPersonalRoomWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto* pc = GetWorld()->GetFirstPlayerController();
	if ( pc )
	{
		pc->bShowMouseCursor = true;
	}

	PlayButton_1Octave->OnClicked.AddDynamic(this , &UPersonalRoomWidget::OnMy1OctaveButtonClick);
	PlayButton_2Octave->OnClicked.AddDynamic(this , &UPersonalRoomWidget::OnMy2OctaveButtonClick);
	PlayButton_3Octave->OnClicked.AddDynamic(this , &UPersonalRoomWidget::OnMy3OctaveButtonClick);

	PauseButton_1Octave->OnClicked.AddDynamic(this , &UPersonalRoomWidget::OnMyStopButtonClick);
	PauseButton_2Octave->OnClicked.AddDynamic(this , &UPersonalRoomWidget::OnMyStopButtonClick);
	PauseButton_3Octave->OnClicked.AddDynamic(this , &UPersonalRoomWidget::OnMyStopButtonClick);

	Button_1Octave->OnClicked.AddDynamic(this , &UPersonalRoomWidget::OnClicked1OctaveButton);
	Button_2Octave->OnClicked.AddDynamic(this , &UPersonalRoomWidget::OnClicked2OctaveButton);
	Button_3Octave->OnClicked.AddDynamic(this , &UPersonalRoomWidget::OnClicked3OctaveButton);

	Button_Man->OnClicked.AddDynamic(this , &UPersonalRoomWidget::OnMyManKeyButtonClick);
	Button_Woman->OnClicked.AddDynamic(this , &UPersonalRoomWidget::OnMyWomanKeyButtonClick);

	audioActor = Cast<APersonalRoomAudio>(UGameplayStatics::GetActorOfClass(GetWorld() , PRAFactory));

	Button_Repeat->OnClicked.AddDynamic(this , &UPersonalRoomWidget::OnClickRepeat);
	Button_Scale->OnClicked.AddDynamic(this , &UPersonalRoomWidget::OnClickScale);


	Button_Back->OnClicked.AddDynamic(this , &UPersonalRoomWidget::OnCancelButtonClick);
}

void UPersonalRoomWidget::OnMy1OctaveButtonClick()
{
	audioActor->PlayAudio(genderCode , 1);
}

void UPersonalRoomWidget::OnMy2OctaveButtonClick()
{
	audioActor->PlayAudio(genderCode , 2);
}

void UPersonalRoomWidget::OnMy3OctaveButtonClick()
{
	audioActor->PlayAudio(genderCode , 3);
}

void UPersonalRoomWidget::OnMyStopButtonClick()
{
	audioActor->StopAudio();
}

void UPersonalRoomWidget::OnMyManKeyButtonClick()
{
	genderCode = 1;
	UTexture2D* ButtonImage;
	if ( bIsMKClicked ) {
		ButtonImage = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/ManKey_Normal.ManKey_Normal'"));
		bIsMKClicked = false;
	}
	else {
		bIsMKClicked = true;
		ButtonImage = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/ManKey_Seleceted.ManKey_Seleceted'"));
	}
	if ( bIsWKClicked ) {
		FSlateBrush tempBrush;
		tempBrush.SetResourceObject(LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/WomanKey_Normal.WomanKey_Normal'")));
		FButtonStyle ButtonStyle = Button_Woman->WidgetStyle;
		ButtonStyle.SetNormal(tempBrush);

		Button_Woman->SetStyle(ButtonStyle);
		bIsWKClicked = false;
	}
	NewBrush.SetResourceObject(ButtonImage);

	FButtonStyle ButtonStyle = Button_Man->WidgetStyle;
	ButtonStyle.SetNormal(NewBrush);

	Button_Man->SetStyle(ButtonStyle);
}

void UPersonalRoomWidget::OnMyWomanKeyButtonClick()
{
	genderCode = 2;
	UTexture2D* ButtonImage;
	if ( bIsWKClicked ) {
		ButtonImage = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/WomanKey_Normal.WomanKey_Normal'"));
		bIsWKClicked = false;
	}
	else {
		bIsWKClicked = true;
		ButtonImage = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/WomanKey_Seleceted.WomanKey_Seleceted'"));
	}
	if ( bIsMKClicked ) {
		FSlateBrush tempBrush;
		tempBrush.SetResourceObject(LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/ManKey_Normal.ManKey_Normal'")));
		FButtonStyle ButtonStyle = Button_Man->WidgetStyle;
		ButtonStyle.SetNormal(tempBrush);

		Button_Man->SetStyle(ButtonStyle);
		bIsMKClicked = false;
	}
	NewBrush.SetResourceObject(ButtonImage);

	FButtonStyle ButtonStyle = Button_Woman->WidgetStyle;
	ButtonStyle.SetNormal(NewBrush);

	Button_Woman->SetStyle(ButtonStyle);
}

void UPersonalRoomWidget::OnClicked1OctaveButton()
{
	UTexture2D* ButtonImage;
	if ( bIs1Clicked ) {
		ButtonImage = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/Octave1_Normal.Octave1_Normal'"));
		bIs1Clicked = false;
	}
	else {
		bIs1Clicked = true;
		ButtonImage = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/Octave1_Selected.Octave1_Selected'"));
	}
	if ( bIs2Clicked ) {
		FSlateBrush tempBrush;
		tempBrush.SetResourceObject(LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/Octave2_Normal.Octave2_Normal'")));
		FButtonStyle ButtonStyle = Button_2Octave->WidgetStyle;
		ButtonStyle.SetNormal(tempBrush);

		Button_2Octave->SetStyle(ButtonStyle);
		bIs2Clicked = false;
	}
	if ( bIs3Clicked ) {
		FSlateBrush tempBrush;
		tempBrush.SetResourceObject(LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/Octave3_Normal.Octave3_Normal'")));
		FButtonStyle ButtonStyle = Button_3Octave->WidgetStyle;
		ButtonStyle.SetNormal(tempBrush);

		Button_3Octave->SetStyle(ButtonStyle);
		bIs3Clicked = false;
	}
	NewBrush.SetResourceObject(ButtonImage);

	FButtonStyle ButtonStyle = Button_1Octave->WidgetStyle;
	ButtonStyle.SetNormal(NewBrush);

	Button_1Octave->SetStyle(ButtonStyle);
}

void UPersonalRoomWidget::OnClicked2OctaveButton()
{
	UTexture2D* ButtonImage;
	if ( bIs2Clicked ) {
		bIs2Clicked = false;
		ButtonImage = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/Octave2_Normal.Octave2_Normal'"));
	}
	else {
		bIs2Clicked = true;
		ButtonImage = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/Octave2_Selected.Octave2_Selected'"));
	}
	if ( bIs1Clicked ) {
		FSlateBrush tempBrush;
		tempBrush.SetResourceObject(LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/Octave1_Normal.Octave1_Normal'")));
		FButtonStyle ButtonStyle = Button_1Octave->WidgetStyle;
		ButtonStyle.SetNormal(tempBrush);

		Button_1Octave->SetStyle(ButtonStyle);
		bIs1Clicked = false;
	}
	if ( bIs3Clicked ) {
		FSlateBrush tempBrush;
		tempBrush.SetResourceObject(LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/Octave3_Normal.Octave3_Normal'")));
		FButtonStyle ButtonStyle = Button_3Octave->WidgetStyle;
		ButtonStyle.SetNormal(tempBrush);

		Button_3Octave->SetStyle(ButtonStyle);
		bIs3Clicked = false;
	}
	NewBrush.SetResourceObject(ButtonImage);

	FButtonStyle ButtonStyle = Button_2Octave->WidgetStyle;
	ButtonStyle.SetNormal(NewBrush);

	Button_2Octave->SetStyle(ButtonStyle);
}

void UPersonalRoomWidget::OnClicked3OctaveButton()
{
	UTexture2D* ButtonImage;
	if ( bIs3Clicked ) {
		bIs3Clicked = false;
		ButtonImage = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/Octave3_Normal.Octave3_Normal'"));
	}
	else {
		bIs3Clicked = true;
		ButtonImage = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/Octave3_Selected.Octave3_Selected'"));
	}
	if ( bIs1Clicked ) {
		FSlateBrush tempBrush;
		tempBrush.SetResourceObject(LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/Octave1_Normal.Octave1_Normal'")));
		FButtonStyle ButtonStyle = Button_1Octave->WidgetStyle;
		ButtonStyle.SetNormal(tempBrush);

		Button_1Octave->SetStyle(ButtonStyle);
		bIs1Clicked = false;
	}
	if ( bIs2Clicked ) {
		FSlateBrush tempBrush;
		tempBrush.SetResourceObject(LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/Octave2_Normal.Octave2_Normal'")));
		FButtonStyle ButtonStyle = Button_2Octave->WidgetStyle;
		ButtonStyle.SetNormal(tempBrush);

		Button_2Octave->SetStyle(ButtonStyle);
		bIs2Clicked = false;
	}

	NewBrush.SetResourceObject(ButtonImage);

	FButtonStyle ButtonStyle = Button_3Octave->WidgetStyle;
	ButtonStyle.SetNormal(NewBrush);

	Button_3Octave->SetStyle(ButtonStyle);
}

void UPersonalRoomWidget::OnClickRepeat()
{
	if ( audioActor ) audioActor->StopAudio();
	UTexture2D* ButtonImage;
	if ( bIsRClicked ) {
		bIsRClicked = false;
		ButtonImage = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/RepeatPractice.RepeatPractice'"));
	}
	else {
		bIsRClicked = true;
		ButtonImage = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/RepeatPractice_Selected.RepeatPractice_Selected'"));
	}
	if ( bIsSClicked ) {
		FSlateBrush tempBrush;
		tempBrush.SetResourceObject(LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/ScalePractice.ScalePractice'")));
		FButtonStyle ButtonStyle = Button_Scale->WidgetStyle;
		ButtonStyle.SetNormal(tempBrush);

		Button_Scale->SetStyle(ButtonStyle);
		bIsSClicked = false;
	}
	NewBrush.SetResourceObject(ButtonImage);

	FButtonStyle ButtonStyle = Button_Repeat->WidgetStyle;
	ButtonStyle.SetNormal(NewBrush);

	Button_Repeat->SetStyle(ButtonStyle);
}

void UPersonalRoomWidget::OnClickScale()
{
	UTexture2D* ButtonImage;
	if ( bIsSClicked ) {
		bIsSClicked = false;
		ButtonImage = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/ScalePractice.ScalePractice'"));
	}
	else {
		bIsSClicked = true;
		ButtonImage = LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/ScalePratice_Selected.ScalePratice_Selected'"));
	}
	if ( bIsRClicked ) {
		FSlateBrush tempBrush;
		tempBrush.SetResourceObject(LoadObject<UTexture2D>(nullptr , TEXT("/Script/Engine.Texture2D'/Game/SHK/resource/Personal_Room/Song_repeat_Practice/RepeatPractice.RepeatPractice'")));
		FButtonStyle ButtonStyle = Button_Repeat->WidgetStyle;
		ButtonStyle.SetNormal(tempBrush);

		Button_Repeat->SetStyle(ButtonStyle);
		bIsRClicked = false;
	}
	NewBrush.SetResourceObject(ButtonImage);

	FButtonStyle ButtonStyle = Button_Scale->WidgetStyle;
	ButtonStyle.SetNormal(NewBrush);

	Button_Scale->SetStyle(ButtonStyle);
}

void UPersonalRoomWidget::OnCancelButtonClick()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	audioActor->StopAudio();
}
