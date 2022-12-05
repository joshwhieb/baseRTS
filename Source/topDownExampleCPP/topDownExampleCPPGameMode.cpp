// Copyright Epic Games, Inc. All Rights Reserved.

#include "topDownExampleCPPGameMode.h"
//#include "topDownExampleCPPPlayerController.h"
//#include "topDownExampleCPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "CameraPlayerController.h"
#include "CameraPawn.h"

AtopDownExampleCPPGameMode::AtopDownExampleCPPGameMode()
{
    PlayerControllerClass = ACameraPlayerController::StaticClass();
    DefaultPawnClass = ACameraPawn::StaticClass();
}