// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceWidget.h"


UResourceWidget::UResourceWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){
    // Do we need to set it visible?
    //TXTGold->SetVisibility(EStateVisibility::Visible);
}

void UResourceWidget::NativeConstruct(){
    Super::NativeConstruct();
}

void UResourceWidget::UpdateGoldCount(int32 Value){
    check(Value >= 0);
    check(TXTGold != nullptr);
    TXTGold->SetText(FText::FromString("Gold: " + FString::FromInt(Value)));
}

void UResourceWidget::UpdateWoodCount(int32 Value){
    check(Value >= 0);
    check(TXTWood != nullptr);
    TXTWood->SetText(FText::FromString("Wood: " + FString::FromInt(Value)));
}