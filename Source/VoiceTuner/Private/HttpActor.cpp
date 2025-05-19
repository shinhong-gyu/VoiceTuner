// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpActor.h"
#include "HttpModule.h"
#include "JsonParseLib.h"
#include "LoginUI.h"
#include "Misc/Paths.h"
#include "CustomizationUI.h"
#include "Components/WidgetSwitcher.h"
#include "HSW_NetGameInstance.h"
#include "LoginGameMode.h"

// Sets default values
AHttpActor::AHttpActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHttpActor::BeginPlay()
{
	Super::BeginPlay();

	gi = Cast<UHSW_NetGameInstance>(GetGameInstance());
	if ( gi && !( gi->GetAccessToken().IsEmpty() ) ) {
		token = gi->GetAccessToken();
	}
	auto* gm = Cast<ALoginGameMode>(GetWorld()->GetAuthGameMode());
	if ( gm ) {
		if ( LoginUIFactory ) {
			LoginUI = CreateWidget<ULoginUI>(GetWorld() , LoginUIFactory);
			if ( LoginUI ) {
				LoginUI->AddToViewport();
				auto* pc = GetWorld()->GetFirstPlayerController();
				if ( pc ) {
					pc->bShowMouseCursor = true;

					FInputModeUIOnly InputMode;
					pc->SetInputMode(InputMode);
				}
			}
		}
	}

}

// Called every frame
void AHttpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHttpActor::LoginRequest(FString id , FString pwd)
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	myID = id;
	myPwd = pwd;

	req->SetURL("http://125.132.216.190:5670/api/auth/login");
	req->SetVerb(TEXT("POST"));
	req->SetHeader(TEXT("content-type") , TEXT("application/json"));
	req->SetContentAsString(UJsonParseLib::MakeLoginInfoJson(id , pwd));

	req->OnProcessRequestComplete().BindUObject(this , &AHttpActor::ResLoginRequest);

	req->ProcessRequest();
}

void AHttpActor::ResLoginRequest(FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully)
{
	if ( bConnectedSuccessfully ) {
		token = UJsonParseLib::TokenJsonParse(Response->GetContentAsString());
		UE_LOG(LogTemp , Warning , TEXT("token : %s") , *token);
		UE_LOG(LogTemp , Warning , TEXT("Response : %s") , *Response->GetContentAsString());
		if ( gi && !myID.IsEmpty() && !myPwd.IsEmpty() && !token.IsEmpty() ) {
			gi->SetID(myID);
			gi->SetPWD(myPwd);
			gi->SetAccessToken(token);
		}
		LoginUI->StartWidgetSwitcher->SetActiveWidgetIndex(1);
	}
	else {
		UE_LOG(LogTemp , Warning , TEXT("Failed"));
	}
}

void AHttpActor::SendSoundFileToServer(const FString& FileName)
{
	TSharedRef<IHttpRequest , ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	Request->SetURL(TEXT("http://125.132.216.190:5670/api/sendOriginVerse"));
	Request->SetVerb(TEXT("POST"));

	FString Boundary = TEXT("----WebKitFormBoundary7MA4YWxkTrZu0gW");

	Request->SetHeader(TEXT("accessToken") , FString::Printf(TEXT("%s") , *token));
	Request->SetHeader(TEXT("content-type") , TEXT("multipart/form-data; boundary=") + Boundary);

	TArray<uint8> FileData;

	UE_LOG(LogTemp , Warning , TEXT("1(), ProcessRequest()"));
	FString FilePath = FPaths::ProjectSavedDir() + TEXT("/BouncedWavFiles/") + FileName + TEXT(".wav");
	temp_Short = FileName;
	if ( FFileHelper::LoadFileToArray(FileData , *FilePath) )
	{
		FString FormData;
		FormData += FString::Printf(TEXT("--%s\r\n") , *Boundary);
		FormData += TEXT("Content-Disposition: form-data; name=\"audio_file\"; filename=\"Sinhodeong_CUT.wav\"\r\n");
		FormData += TEXT("content-Type: audio/wav\r\n\r\n");

		TArray<uint8> Body;
		Body.Append((uint8*)TCHAR_TO_UTF8(*FormData) , FormData.Len());
		Body.Append(FileData);

		FString EndBoundary = TEXT("\r\n--") + Boundary + TEXT("--\r\n");
		Body.Append((uint8*)TCHAR_TO_UTF8(*EndBoundary) , EndBoundary.Len());

		Request->SetContent(Body);

		Request->SetHeader(TEXT("content-length") , FString::FromInt(Body.Num()));
		Request->OnProcessRequestComplete().BindUObject(this , &AHttpActor::ResSendSoundFileToServer);

		Request->ProcessRequest();
		UE_LOG(LogTemp , Warning , TEXT("SendSoundFileToServer() -  ProcessRequest()"));
	}
}

void AHttpActor::ResSendSoundFileToServer(FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully)
{
	if ( bConnectedSuccessfully ) {
		UE_LOG(LogTemp , Warning , TEXT("Success : %s") , *Response->GetContentAsString());
		solution_10 = UJsonParseLib::ReturnJsonParse(Response->GetContentAsString());
		FString FilePath = FPaths::ProjectContentDir() + temp_Short + TEXT("_solution.txt");
		if ( FFileHelper::SaveStringToFile(solution_10 , *FilePath) )
		{
			UE_LOG(LogTemp , Warning , TEXT("save success : %s") , *FilePath);
		}
		else
		{
			UE_LOG(LogTemp , Error , TEXT("Failed success : %s") , *FilePath);
		}
	}
	else {
		UE_LOG(LogTemp , Warning , TEXT("Failed"));
	}
}

void AHttpActor::SendOriginSoundFileToServer(const FString& FileName)
{
	TSharedRef<IHttpRequest , ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	Request->SetURL(TEXT("http://125.132.216.190:5670/api/sendSaveSolution"));
	Request->SetVerb(TEXT("POST"));

	FString Boundary = TEXT("----WebKitFormBoundary7MA4YWxkTrZu0gW");

	Request->SetHeader(TEXT("accessToken") , FString::Printf(TEXT("%s") , *token));
	Request->SetHeader(TEXT("content-type") , TEXT("multipart/form-data; boundary=") + Boundary);

	TArray<uint8> FileData;

	UE_LOG(LogTemp , Warning , TEXT("1(), ProcessRequest()"));
	FString FilePath = FPaths::ProjectSavedDir() + TEXT("/BouncedWavFiles/") + FileName + TEXT(".wav");
	temp_Long = FileName;
	if ( FFileHelper::LoadFileToArray(FileData , *FilePath) )
	{
		FString FormData;
		FormData += FString::Printf(TEXT("--%s\r\n") , *Boundary);
		FormData += TEXT("Content-Disposition: form-data; name=\"audio_file\"; filename=\"Sinhodeong_CUT.wav\"\r\n");
		FormData += TEXT("content-Type: audio/wav\r\n\r\n");

		TArray<uint8> Body;
		Body.Append((uint8*)TCHAR_TO_UTF8(*FormData) , FormData.Len());
		Body.Append(FileData);

		FString EndBoundary = TEXT("\r\n--") + Boundary + TEXT("--\r\n");
		Body.Append((uint8*)TCHAR_TO_UTF8(*EndBoundary) , EndBoundary.Len());

		Request->SetContent(Body);

		Request->SetHeader(TEXT("content-length") , FString::FromInt(Body.Num()));
		Request->OnProcessRequestComplete().BindUObject(this , &AHttpActor::ResSendOriginSoundFileToServer);

		Request->ProcessRequest();
		UE_LOG(LogTemp , Warning , TEXT("SendSoundOriginFileToServer() - ProcessRequest()"));
	}
}

void AHttpActor::ResSendOriginSoundFileToServer(FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully)
{
	if ( bConnectedSuccessfully ) {
		solution_10 = UJsonParseLib::ReturnJsonParse(Response->GetContentAsString());
		FString FilePath = FPaths::ProjectContentDir() + temp_Long + "_solution.txt";
		if ( FFileHelper::SaveStringToFile(solution_10 , *FilePath) )
		{
			UE_LOG(LogTemp , Warning , TEXT("파일 저장 성공: %s") , *FilePath);
		}
		else
		{
			UE_LOG(LogTemp , Error , TEXT("파일 저장 실패: %s") , *FilePath);
		}
	}
	else {
		UE_LOG(LogTemp , Warning , TEXT("Failed"));
	}
}

