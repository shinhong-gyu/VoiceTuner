// Fill out your copyright notice in the Description page of Project Settings.


#include "ResultWIdget.h"
#include "Components/TextBlock.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"



void UResultWIdget::NativeConstruct()
{
	Button_ReqAIFeedBack->OnClicked.AddDynamic(this,&UResultWIdget::OnClickFeedBackButton);
}

void UResultWIdget::NativeTick(const FGeometry& MyGeoMetry , float InDeltaTime)
{
	Super::NativeTick(MyGeoMetry,InDeltaTime);
// 	FString FilePath = FPaths::ProjectContentDir() + TEXT("Sinhodeong_CUT_solution.txt");
// 	FString LoadText;
// 
// 	if ( FFileHelper::LoadFileToString(LoadText , *FilePath) ) {
// 	
// 	}
}

void UResultWIdget::SetScore(int32 Score)
{
	TB_Score->SetText(FText::AsNumber(Score));
}

void UResultWIdget::OnClickFeedBackButton()
{
	UKismetSystemLibrary::LaunchURL("http://125.132.216.190:8989/");
}
