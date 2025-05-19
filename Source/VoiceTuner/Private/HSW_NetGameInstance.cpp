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

		// ����� ��û -> ����
		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this , &UHSW_NetGameInstance::OnMyCreateSessionComplete);

		// ��ã�� ����
		SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this , &UHSW_NetGameInstance::OnMyFindSessionsCompleteDelegates);

		// ������ ����
		SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this , &UHSW_NetGameInstance::OnMyJoinSessionComplete);

		// ������ ����
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

	// 1. ���뼭���� ����ϴ°�?
	settings.bIsDedicated = false;

	// 2. ����(Lan)���� ��ġ�ϴ°�?
	FName subsysName = IOnlineSubsystem::Get()->GetSubsystemName();
	settings.bIsLANMatch = subsysName == "NULL";

	// 3. ��Ī�� ����(true)Ȥ�� �����(false, �ʴ븦 ���ؼ� ��Ī)
	settings.bShouldAdvertise = true;

	// 4. ������ ���� ����(�¶���/�ڸ����/���) ��� ����
	settings.bUsesPresence = true;

	// 5. �߰��� ���� �����Ѱ�?
	settings.bAllowJoinViaPresence = true;
	settings.bAllowJoinInProgress = true;

	// 6. �ִ� �ο���
	settings.NumPublicConnections = playerCount;

	// 7. Ŀ���� ����
	settings.Set(FName("ROOM_NAME") , roomName , EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	settings.Set(FName("HOST_NAME") , MySessionName , EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	//������������ 

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

		// ������ ������ ������ʹ�.
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

			// ���̸�
			ret.Session.SessionSettings.Get(FName("ROOM_NAME") , roomInfo.roomName);
			// ȣ��Ʈ�̸�
			ret.Session.SessionSettings.Get(FName("HOST_NAME") , roomInfo.hostName);
			// �ִ� �÷��̾� ��
			roomInfo.maxPlayerCount = ret.Session.SessionSettings.NumPublicConnections;
			// ������ �÷��̾� ��(�ִ� - ����)
			roomInfo.currentPlayerCount = roomInfo.maxPlayerCount - ret.Session.NumOpenPublicConnections;
			// �� ����
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
		// ������ �ִ� ������ ������ ������ �ʹ�.
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
	// ������ ��û
	SessionInterface->DestroySession(FName(MySessionName));
}

void UHSW_NetGameInstance::OnMyDestroySessionComplete(FName SessionName , bool bWasSuccessful)
{
	if ( bWasSuccessful )
	{
		// Ŭ���̾�Ʈ�� �κ�� ������ ����ʹ�.
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