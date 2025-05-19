// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUI.h"
#include "Components/Button.h"
#include "HttpActor.h"
#include "Components/EditableText.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "HSW_NetGameInstance.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Image.h"

void ULoginUI::NativeConstruct()
{
	HttpActor = Cast<AHttpActor>(UGameplayStatics::GetActorOfClass(GetWorld() , HAFactory));

	LoginButton->OnClicked.AddDynamic(this , &ULoginUI::OnMyButtonClicked);

	Button_NameInputClear->OnClicked.AddDynamic(this , &ULoginUI::OnMyClearButtonClick);

	UserIdPrompt->OnTextCommitted.AddDynamic(this , &ULoginUI::OnMyIDCommitted);

	UserPwdPrompt->OnTextCommitted.AddDynamic(this , &ULoginUI::OnMyPwdCommitted);

	ET_UserNamePrompt->OnTextCommitted.AddDynamic(this , &ULoginUI::OnMyUserNameCommited);

	Button_Commit->OnClicked.AddDynamic(this , &ULoginUI::OnMyCommitButtonClick);
}

void ULoginUI::OnMyButtonClicked()
{
	UserIdPrompt->SetText(FText());
	UserPwdPrompt->SetText(FText());
	if ( !id.IsEmpty() && !pwd.IsEmpty() ) {
		HttpActor->LoginRequest(id , pwd);
	}
	else {
		UserIdPrompt->SetUserFocus(GetWorld()->GetFirstPlayerController());
		UserIdPrompt->SetKeyboardFocus();
	}
}

void ULoginUI::OnMyIDCommitted(const FText& Text , ETextCommit::Type CommitMethod)
{
	if ( CommitMethod == ETextCommit::OnEnter || CommitMethod == ETextCommit::OnUserMovedFocus )
	{
		id = Text.ToString();
	}
}

void ULoginUI::OnMyPwdCommitted(const FText& Text , ETextCommit::Type CommitMethod)
{
	if ( CommitMethod == ETextCommit::OnEnter || CommitMethod == ETextCommit::OnUserMovedFocus )
	{
		pwd = Text.ToString();
	}
}

void ULoginUI::OnMyUserNameCommited(const FText& Text , ETextCommit::Type CommitMethod)
{
	if ( CommitMethod == ETextCommit::OnEnter || CommitMethod == ETextCommit::OnUserMovedFocus )
	{
		userName = Text.ToString();
	}
}

void ULoginUI::OnMyClearButtonClick()
{
	ET_UserNamePrompt->SetText(FText::FromString(""));
}


void ULoginUI::OnMyCommitButtonClick()
{
	auto* gi = Cast<UHSW_NetGameInstance>(GetWorld()->GetGameInstance());
	if ( gi ) gi->SetName(userName);
	FName LobbyLevelName = "Alpha_Stage";
	UGameplayStatics::OpenLevel(this , LobbyLevelName);
}



