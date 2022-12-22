// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "ResourceWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNEXAMPLECPP_API UResourceWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UResourceWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void UpdateGoldCount(int32 Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TXTGold;
};
