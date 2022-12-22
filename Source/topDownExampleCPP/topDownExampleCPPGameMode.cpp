// Copyright Epic Games, Inc. All Rights Reserved.

#include "topDownExampleCPPGameMode.h"
//#include "topDownExampleCPPPlayerController.h"
//#include "topDownExampleCPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "CameraPlayerController.h"
#include "CameraPawn.h"
#include "RTSHUD.h"

AtopDownExampleCPPGameMode::AtopDownExampleCPPGameMode()
{
    PlayerControllerClass = ACameraPlayerController::StaticClass();
    DefaultPawnClass = ACameraPawn::StaticClass();
    
    //HUDClass = ARTSHUD::StaticClass();
    static ConstructorHelpers::FClassFinder<ARTSHUD> RTSBPClass(TEXT("/Game/TopDown/Blueprints/BP_RTSHUD"));
    if(RTSBPClass.Class != nullptr){
        HUDClass = RTSBPClass.Class;
    }

}