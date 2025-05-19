// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpActor.generated.h"

UCLASS()
class VOICETUNER_API AHttpActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHttpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame2
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ULoginUI> LoginUIFactory;

	UPROPERTY()
	class ULoginUI* LoginUI;

	UPROPERTY()
	class UCustomizationUI* CustomUI;



	void LoginRequest(FString id , FString pwd);

	void ResLoginRequest(FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully);

	UFUNCTION(BlueprintCallable)
	void SendSoundFileToServer(const FString& FileName);

	void ResSendSoundFileToServer(FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully);

	UFUNCTION(BlueprintCallable)
	void SendOriginSoundFileToServer(const FString& FileName);

	void ResSendOriginSoundFileToServer(FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully);

	FString token;
	FString myID = "shinhonggyu";
	FString myPwd;
	FString song_id = "song_456";
	FString track_id = "track_789";

	FString solution_10;

	FString CurrentLevelName;

	FString temp_Short;
	FString temp_Long;

	TMap<FString , FString> userInfo;

	class UHSW_NetGameInstance* gi;
};
