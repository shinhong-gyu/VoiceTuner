// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JsonParseLib.generated.h"

/**
 *
 */
UCLASS()
class VOICETUNER_API UJsonParseLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FString TokenJsonParse(const FString& json);

	static FString ReturnJsonParse(const FString& json);

	static FString MakeLoginInfoJson(FString id , FString pwd);

	static FString MakeSoundFileDate(long user_id , long song_id);

	static FString MakeUserInfoJson(const TMap<FString , FString> source);
};
