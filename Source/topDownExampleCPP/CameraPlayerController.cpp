// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPlayerController.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"

ACameraPlayerController::ACameraPlayerController(){
    bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::EyeDropper;
}

void ACameraPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &ACameraPlayerController::SelectionPressed);
	InputComponent->BindAction("LeftMouseClick", IE_Released, this, &ACameraPlayerController::SelectionReleased);

	InputComponent->BindAction("RightMouseClick", IE_Released, this, &ACameraPlayerController::MoveReleased);
}


void ACameraPlayerController::BeginPlay(){

	Super::BeginPlay();

	HudPtr = Cast<ARTSHUD>(GetHUD());
}

void ACameraPlayerController::SelectionPressed(){
	
	if(HudPtr != nullptr){
		HudPtr->InitialPoint = HudPtr->GetMousePos2D();
		HudPtr->bStartSelecting = true;
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Nullptr controller HUD pointer"));
	}

}

void ACameraPlayerController::SelectionReleased(){

    if (HudPtr != nullptr){
		HudPtr->bStartSelecting = false;
		SelectedActors = HudPtr->FoundActors;
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Nullptr controller HUD pointer"));
	}

}

void ACameraPlayerController::MoveReleased(){
	
	FVector MoveLocation;
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
	bool bHitSuccessful = false;
	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	
	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	if (SelectedActors.Num() > 0){
		for(int32 i=0; i < SelectedActors.Num(); i++){
			MoveLocation = Hit.Location + FVector(i / 2 * 100, i % 2 * 100, 0);
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedActors[i]->GetController(), MoveLocation);
			//FORCEINLINE void DrawDebugSphere(const UWorld* InWorld, FVector const& Center, float Radius, int32 Segments, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f) {}
			DrawDebugSphere(GetWorld(), MoveLocation, 25.0, 10, FColor::Red, false, 3.0);
		}
	}
}
