// Fill out your copyright notice in the Description page of Project Settings.


#include "LyricsWidget.h"
#include "Components/TextBlock.h"
#include "VoiceTunerCharacter.h"
#include "PointComponent.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

void ULyricsWidget::NativeTick(const FGeometry& MyGeometry , float InDeltaTime)
{
	Super::NativeTick(MyGeometry , InDeltaTime);

	auto* player = Cast<AVoiceTunerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if ( player ) {
		TB_Score->SetText(FText::AsNumber(player->GetPointComponent()->GetPoint()));
	}
}