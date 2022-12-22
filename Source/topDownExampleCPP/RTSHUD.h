// Fill out your copyright notice in the Description page of Project Settings.

// DOCS?
// https://www.youtube.com/watch?v=lYfXkxlInVI

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "topDownExampleCPPCharacter.h"
#include "Components/WidgetComponent.h"
#include "ResourceWidget.h"

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

	UPROPERTY()
	bool bStartSelecting = false;

	UPROPERTY()
	TArray<AtopDownExampleCPPCharacter*> FoundActors;


	ARTSHUD();

	FVector2D GetMousePos2D();

	virtual void DrawHUD() override; // Same essentially as the tick method for other class types.

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void UpdateGoldCount(int32 Value);

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> GoldWidgetClass;

private:

	UResourceWidget* GoldWidget;
};
