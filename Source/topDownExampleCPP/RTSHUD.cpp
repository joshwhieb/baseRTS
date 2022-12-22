// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSHUD.h"

ARTSHUD::ARTSHUD(){

}

void ARTSHUD::BeginPlay(){
    Super::BeginPlay();

    if(GoldWidgetClass){
        GoldWidget = CreateWidget<UResourceWidget>(GetWorld(), GoldWidgetClass);

        if(GoldWidget){
            GoldWidget->AddToViewport();
        }
    }
}

void ARTSHUD::Tick(float DeltaSeconds){
    Super::Tick(DeltaSeconds);


}

void ARTSHUD::DrawHUD(){
    Super::DrawHUD();

    if (bStartSelecting){
        //if (FoundActors.Num() > 0){
        //    for (int32 i=0; i < FoundActors.Num(); i++){
        //        FoundActors[i]->SetDeselected();
        //    }
        //}
        FoundActors.Empty();

        CurrentPoint = GetMousePos2D();
        DrawRect(FLinearColor(0,0,1,.15f), InitialPoint.X, InitialPoint.Y, CurrentPoint.X - InitialPoint.X, CurrentPoint.Y - InitialPoint.Y);
        
        GetActorsInSelectionRectangle<AtopDownExampleCPPCharacter>(InitialPoint, CurrentPoint, FoundActors, false, false);

        /*if (FoundActors.Num() > 0){
            for (int32 i=0; i < FoundActors.Num(); i++){
                FoundActors[i]->SetSelected();
            }
        }*/
    }
}

FVector2D ARTSHUD::GetMousePos2D(){
    float posX, posY;
    GetOwningPlayerController()->GetMousePosition(posX, posY);

    return FVector2D(posX, posY);
}

void ARTSHUD::UpdateGoldCount(int32 Value){
    if (GoldWidget){
        GoldWidget->UpdateGoldCount(Value);
    }
}
