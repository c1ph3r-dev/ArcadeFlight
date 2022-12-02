// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArcadeFlightGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ARCADEFLIGHT_API AArcadeFlightGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> WidgetClass;
	
	UUserWidget* UI;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	int Score;
protected:
	virtual void BeginPlay() override;

public:
	void AddScore();
};
