// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTSHUD.h"
#include "topDownExampleCPPCharacter.h"
#include "CameraPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNEXAMPLECPP_API ACameraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ACameraPlayerController();

	virtual void BeginPlay() override;

	ARTSHUD* HudPtr;

protected:

	FVector CachedDestination;

	UPROPERTY()
	TArray<AtopDownExampleCPPCharacter*> SelectedActors;

	virtual void SetupInputComponent() override;

	UFUNCTION()
	void MoveReleased();

	UFUNCTION()
	void SelectionReleased();

	UFUNCTION()
	void SelectionPressed();

};
