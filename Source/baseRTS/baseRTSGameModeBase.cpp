// Copyright Epic Games, Inc. All Rights Reserved.


#include "baseRTSGameModeBase.h"
#include "CameraPlayerController.h"
#include "CameraPawn.h"

AbaseRTSGameModeBase::AbaseRTSGameModeBase() {
    PlayerControllerClass = ACameraPlayerController::StaticClass();
    DefaultPawnClass = ACameraPawn::StaticClass();
}
