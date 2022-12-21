// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "topDownExampleCPPCharacter.h"

#include "RTSHUD.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNEXAMPLECPP_API ARTSHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FVector2D InitialPoint;

	UPROPERTY()
	FVector2D CurrentPoint;

	FVector2D GetMousePos2D();

	virtual void DrawHUD() override; // Same essentially as the tick method for other class types.

	UPROPERTY()
	bool bStartSelecting = false;

	UPROPERTY()
	TArray<AtopDownExampleCPPCharacter*> FoundActors;

};
