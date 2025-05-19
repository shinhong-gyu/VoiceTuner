// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineSessionInterface.h"
#include "HSW_NetGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FRoomInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString roomName;
	UPROPERTY(BlueprintReadOnly)
	FString hostName;
	UPROPERTY(BlueprintReadOnly)
	FString songName;
	UPROPERTY(BlueprintReadOnly)
	int32 maxPlayerCount;
	UPROPERTY(BlueprintReadOnly)
	int32 currentPlayerCount;
	UPROPERTY(BlueprintReadOnly)
	int32 pingMS;

	int32 index;

	FString ToString()
	{
		return FString::Printf(TEXT("%d)[%s][%s] (%d / %d) -> %dms") , index , *roomName , *hostName , currentPlayerCount , maxPlayerCount , pingMS);
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSearchSignature , const struct FRoomInfo& , info);
/**
 *
 */
UCLASS()
class VOICETUNER_API UHSW_NetGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	IOnlineSessionPtr SessionInterface;

	FString MySessionName = TEXT("H-SeungWoo");
	FString WavFilePath;
	FString SongName;

	// �� ���� ================================================
	//����� ��û
	UFUNCTION()
	void CreateMySession(FString roomName , int32 playerCount);

	// ����� ����
	UFUNCTION()
	void OnMyCreateSessionComplete(FName SessionName , bool bWasSuccessful);

	// �� �˻� ===================================================
	// ã�� ���� ���
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	// �� ã�� ��û
	void FindOtherSessions();
	// �� ã�� ����
	void OnMyFindSessionsCompleteDelegates(bool bWasSuccessful);

	FSearchSignature OnSearchSignatureCompleteDelegate;

	// �� ���� ====================================================
	// ������ ��û
	void JoinSession(int32 index);
	// ������ ����
	void OnMyJoinSessionComplete(FName SessionName , EOnJoinSessionCompleteResult::Type EOnJoinSessionCompleteResult);


	// �� ���� ====================================================
	// ������ ��û -> UI���� ȣ��
	UFUNCTION(BlueprintCallable)
	void ExitSession();

	UFUNCTION(Server , Reliable)
	void ServerRPCExitSession();

	UFUNCTION(NetMulticast , Reliable)
	void MulticastRPCExitSession();

	// ������ ����
	void OnMyDestroySessionComplete(FName SessionName , bool bWasSuccessful);

	// �α��� ���� Set/Get
	void SetAccessToken(FString p_AccessToken);
	FString GetAccessToken() const;
	void SetID(FString p_UserID);
	FString GetID() const;
	void SetPWD(FString p_UserPWD);
	FString GetPWD() const;
	void SetName(FString p_UserName);
	UFUNCTION(BlueprintCallable)
	FString GetName() const;
	
private:
	// �α��� ����
	FString accessToken;
	FString userID;
	FString userPWD;
	FString userName;
};
