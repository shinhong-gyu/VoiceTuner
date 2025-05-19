// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginUI.generated.h"

/**
 *
 */
UCLASS()
class VOICETUNER_API ULoginUI : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	UPROPERTY(meta = ( BindWidget ))
	class UWidgetSwitcher* StartWidgetSwitcher;

	// ===============LoginPanel=====================
	UPROPERTY(meta = ( BindWidget ))
	class UButton* LoginButton;

	UPROPERTY(meta = ( BindWidget ))
	class UEditableText* UserIdPrompt;

	UPROPERTY(meta = ( BindWidget ))
	class UEditableText* UserPwdPrompt;

	UFUNCTION()
	void OnMyButtonClicked();

	UPROPERTY(EditDefaultsOnly)
	class AHttpActor* HttpActor;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AHttpActor> HAFactory;

	UFUNCTION()
	void OnMyIDCommitted(const FText& Text , ETextCommit::Type CommitMethod);
	UFUNCTION()
	void OnMyPwdCommitted(const FText& Text , ETextCommit::Type CommitMethod);

	FString id;
	FString pwd;
	//======================CustomUI======================
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Button_Commit;
	UPROPERTY(meta = ( BindWidget ))
	class UButton* Button_NameInputClear;

	UPROPERTY(meta = ( BindWidget ))
	class UEditableText* ET_UserNamePrompt;


	UFUNCTION()
	void OnMyUserNameCommited(const FText& Text , ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnMyCommitButtonClick();

	FString userName;

	UFUNCTION()
	void OnMyClearButtonClick();

};
