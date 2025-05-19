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

	// 방 생성 ================================================
	//방생성 요청
	UFUNCTION()
	void CreateMySession(FString roomName , int32 playerCount);

	// 방생성 응답
	UFUNCTION()
	void OnMyCreateSessionComplete(FName SessionName , bool bWasSuccessful);

	// 방 검색 ===================================================
	// 찾을 방의 목록
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	// 방 찾기 요청
	void FindOtherSessions();
	// 방 찾기 응답
	void OnMyFindSessionsCompleteDelegates(bool bWasSuccessful);

	FSearchSignature OnSearchSignatureCompleteDelegate;

	// 방 입장 ====================================================
	// 방입장 요청
	void JoinSession(int32 index);
	// 방입장 응답
	void OnMyJoinSessionComplete(FName SessionName , EOnJoinSessionCompleteResult::Type EOnJoinSessionCompleteResult);


	// 방 퇴장 ====================================================
	// 방퇴장 요청 -> UI에서 호출
	UFUNCTION(BlueprintCallable)
	void ExitSession();

	UFUNCTION(Server , Reliable)
	void ServerRPCExitSession();

	UFUNCTION(NetMulticast , Reliable)
	void MulticastRPCExitSession();

	// 방퇴장 응답
	void OnMyDestroySessionComplete(FName SessionName , bool bWasSuccessful);

	// 로그인 정보 Set/Get
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
	// 로그인 정보
	FString accessToken;
	FString userID;
	FString userPWD;
	FString userName;
};
