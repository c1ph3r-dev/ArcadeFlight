// Copyright Epic Games, Inc. All Rights Reserved.


#include "ArcadeFlightGameModeBase.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/GameUI.h"

void AArcadeFlightGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetClass)
	{
		UI = CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), WidgetClass);
		if (UI)
		{
			UI->AddToViewport();
			UI->SetVisibility(ESlateVisibility::Visible);
			const auto HUD = Cast<UGameUI>(UI);
			if(HUD)
			{
				HUD->SetScore(0);
			}
		}
	}
}

void AArcadeFlightGameModeBase::AddScore()
{
	const auto HUD = Cast<UGameUI>(UI);
	if(HUD)
	{
		HUD->SetScore(++Score);
	}
}
