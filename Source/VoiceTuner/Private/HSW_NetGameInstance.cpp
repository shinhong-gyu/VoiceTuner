// Fill out your copyright notice in the Description page of Project Settings.


#include "HSW_NetGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "VoiceTuner.h"
#include "../../../../Plugins/Online/OnlineBase/Source/Public/Online/OnlineSessionNames.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void UHSW_NetGameInstance::Init()
{
	Super::Init();

	if ( auto* subSystem = IOnlineSubsystem::Get() )
	{
		SessionInterface = subSystem->GetSessionInterface();

		// 방생성 요청 -> 응답
		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this , &UHSW_NetGameInstance::OnMyCreateSessionComplete);

		// 방찾기 응답
		SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this , &UHSW_NetGameInstance::OnMyFindSessionsCompleteDelegates);

		// 방입장 응답
		SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this , &UHSW_NetGameInstance::OnMyJoinSessionComplete);

		// 방퇴장 응답
		SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this , &UHSW_NetGameInstance::OnMyDestroySessionComplete);
	}

	//PRINTLOG(TEXT("Network Start!!"));
	//FTimerHandle handle;
	//GetWorld()->GetTimerManager().SetTimer(handle , [&]() {
	//	/*CreateMySession(MySessionName , 10);*/
	//	FindOtherSessions();
	//	} , 3 , false);

}

void UHSW_NetGameInstance::CreateMySession(FString roomName , int32 playerCount)
{
	FOnlineSessionSettings settings;

	// 1. 전용서버를 사용하는가?
	settings.bIsDedicated = false;

	// 2. 랜선(Lan)으로 매치하는가?
	FName subsysName = IOnlineSubsystem::Get()->GetSubsystemName();
	settings.bIsLANMatch = subsysName == "NULL";

	// 3. 매칭이 공개(true)혹은 비공개(false, 초대를 통해서 매칭)
	settings.bShouldAdvertise = true;

	// 4. 유저의 상태 정보(온라인/자리비움/등등) 사용 여부
	settings.bUsesPresence = true;

	// 5. 중간에 난입 가능한가?
	settings.bAllowJoinViaPresence = true;
	settings.bAllowJoinInProgress = true;

	// 6. 최대 인원수
	settings.NumPublicConnections = playerCount;

	// 7. 커스텀 정보
	settings.Set(FName("ROOM_NAME") , roomName , EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	settings.Set(FName("HOST_NAME") , MySessionName , EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	//음악파일정보 

	settings.Set(FName("Song_Name") , SongName , EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	FUniqueNetIdPtr netID = GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().GetUniqueNetId();

	SessionInterface->CreateSession(*netID , FName(MySessionName) , settings);

	PRINTLOG(TEXT("Create Session Start roomName : %s / hostName : %s") , *roomName , *MySessionName);
}

void UHSW_NetGameInstance::OnMyCreateSessionComplete(FName SessionName , bool bWasSuccessful)
{
	if ( bWasSuccessful )
	{
		PRINTLOG(TEXT("OnMyCreateSessionComplete is Success~~~~~"));

		// 서버가 여행을 떠나고싶다.
		//GetWorld()->ServerTravel(TEXT("/Game/HSW/Maps/HSW_Alpha_MultiStage?listen"));
		GetWorld()->ServerTravel(TEXT("/Game/TA/Levels/Multi_Stage?listen"));
	}
	else
	{
		PRINTLOG(TEXT("OnMyCreateSessionComplete is Failed!!!"));
	}
}

void UHSW_NetGameInstance::FindOtherSessions()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch);

	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE , true , EOnlineComparisonOp::Equals);
	SessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";
	SessionSearch->MaxSearchResults = 40;

	SessionInterface->FindSessions(0 , SessionSearch.ToSharedRef());
}

void UHSW_NetGameInstance::OnMyFindSessionsCompleteDelegates(bool bWasSuccessful)
{
	if ( bWasSuccessful )
	{
		TArray<FOnlineSessionSearchResult> results = SessionSearch->SearchResults;

		for ( int32 i = 0; i < results.Num(); i++ )
		{
			FOnlineSessionSearchResult ret = results[i];
			if ( false == ret.IsValid() )
			{
				continue;
			}

			FRoomInfo roomInfo;
			roomInfo.index = i;

			// 방이름
			ret.Session.SessionSettings.Get(FName("ROOM_NAME") , roomInfo.roomName);
			// 호스트이름
			ret.Session.SessionSettings.Get(FName("HOST_NAME") , roomInfo.hostName);
			// 최대 플레이어 수
			roomInfo.maxPlayerCount = ret.Session.SessionSettings.NumPublicConnections;
			// 입장한 플레이어 수(최대 - 남은)
			roomInfo.currentPlayerCount = roomInfo.maxPlayerCount - ret.Session.NumOpenPublicConnections;
			// 핑 정보
			roomInfo.pingMS = ret.PingInMs;

			if ( OnSearchSignatureCompleteDelegate.IsBound() )
				OnSearchSignatureCompleteDelegate.Broadcast(roomInfo);

			PRINTLOG(TEXT("%s") , *roomInfo.ToString());
		}
	}
	else
	{
		PRINTLOG(TEXT("OnMyFindSessionsCompleteDelegates is Failed!!!"));
	}
}

void UHSW_NetGameInstance::JoinSession(int32 index)
{
	auto result = SessionSearch->SearchResults[index];
	SessionInterface->JoinSession(0 , FName(MySessionName) , result);
}

void UHSW_NetGameInstance::OnMyJoinSessionComplete(FName SessionName , EOnJoinSessionCompleteResult::Type EOnJoinSessionCompleteResult)
{
	if ( EOnJoinSessionCompleteResult::Success == EOnJoinSessionCompleteResult )
	{
		// 서버가 있는 레벨로 여행을 떠나고 싶다.
		auto* pc = GetWorld()->GetFirstPlayerController();

		FString url;
		SessionInterface->GetResolvedConnectString(SessionName , url);
		if ( false == url.IsEmpty() )
		{
			pc->ClientTravel(url , ETravelType::TRAVEL_Absolute);
		}
	}
}

void UHSW_NetGameInstance::ExitSession()
{
	ServerRPCExitSession();
}

void UHSW_NetGameInstance::ServerRPCExitSession_Implementation()
{
	MulticastRPCExitSession();
}

void UHSW_NetGameInstance::MulticastRPCExitSession_Implementation()
{
	// 방퇴장 요청
	SessionInterface->DestroySession(FName(MySessionName));
}

void UHSW_NetGameInstance::OnMyDestroySessionComplete(FName SessionName , bool bWasSuccessful)
{
	if ( bWasSuccessful )
	{
		// 클라이언트가 로비로 여행을 가고싶다.
		auto* pc = GetWorld()->GetFirstPlayerController();
		pc->ClientTravel(TEXT("/Game/TA/Levels/Alpha_Stage") , ETravelType::TRAVEL_Absolute);
	}
}

void UHSW_NetGameInstance::SetAccessToken(FString p_AccessToken)
{
	accessToken = p_AccessToken;
}

FString UHSW_NetGameInstance::GetAccessToken() const
{
	return accessToken;
}

void UHSW_NetGameInstance::SetID(FString p_UserID)
{
	userID = p_UserID;
}

FString UHSW_NetGameInstance::GetID() const
{
	return userID;
}

void UHSW_NetGameInstance::SetPWD(FString p_UserPWD)
{
	userPWD = p_UserPWD;
}

FString UHSW_NetGameInstance::GetPWD() const
{
	return userPWD;
}

void UHSW_NetGameInstance::SetName(FString p_UserName)
{
	userName = p_UserName;
}

FString UHSW_NetGameInstance::GetName() const
{
	return userName;
}