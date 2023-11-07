// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPlayerController.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "RTSHUD.h"
#include "Engine/EngineTypes.h"
#include "topDownExampleCPPCharacter.h"
#include "GameFramework/DamageType.h"
#include "Engine/DamageEvents.h"

// TODO(jhieb) remove just testing for Fdmgevent.
#include "GameFramework/Character.h"

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
	//GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
	bool bHitSuccessful = false;
	
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0); // Get the PlayerController
	FVector WorldLocation, WorldDirection;
	MyPlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	FHitResult HitResult; // Store information about the hit

	ECollisionChannel TraceChannel = ECC_Visibility; // You can change the collision channel to match your setup

	// Perform the line trace from the mouse cursor location
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	AActor* HitActor = Hit.GetActor(); // Get the actor that was hit
	if (HitActor)
	{
		//UE_LOG(LogTemp, Warning, TEXT("HIT SOMETHING"))
		// Handle the hit actor here
		AtopDownExampleCPPCharacter* villager_actor = Cast<AtopDownExampleCPPCharacter>(HitActor);
		if(villager_actor != nullptr){
			FDamageEvent DamageEvent;
			float DmgTaken = villager_actor->TakeDamage(10, DamageEvent, this, villager_actor); 
		}
	}
	
	// Now, draw a debug line to visualize the trace
	FVector StartLocation = MyPlayerController->PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = Hit.ImpactPoint;

	// Draw the debug line
	DrawDebugLine(
		GetWorld(),
		StartLocation,
		EndLocation,
		FColor(255, 0, 0), // Line color (red in this example)
		false, // Persistent (false for a one-time debug line)
		1, // Line thickness
		0, // Depth priority
		100 // Duration (set to 1 to display for one frame)
	);
	UE_LOG(LogTemp, Warning, TEXT("StartLocation: %s, EndLocation: %s"), *StartLocation.ToString(), *EndLocation.ToString());
	/*
	
	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	//GetHitResultUnderCursorByChannel()
	AActor* hit_actor = Cast<AtopDownExampleCPPCharacter>(Hit.GetActor());
	FVector MousePosition;
	GetMousePosition(MousePosition.X, MousePosition.Y);
	FVector WorldLocation;
	DeprojectMousePositionToWorld(MousePosition, WorldLocation);

	GetWorld()->

	// TODO(jhieb) this shouldn't happen in the controller it should be done by the selected character(s).
	if(hit_actor != nullptr){
		// figure out the type of actor.
		// TODO(Jhieb) is there a more foolproof way of getting the actor type?
		AtopDownExampleCPPCharacter* villager_actor = Cast<AtopDownExampleCPPCharacter>(hit_actor);
		if(villager_actor != nullptr){
			int dmg = 10;
			FVector shotDirection;

			// TODO(jhieb) kind of fudging the parameters ATM.  The actor that caused dmg needs to be figured out.
			//FPointDamageEvent DamageEvent(10, Hit, rotation, shotDirection, nullptr);
			//float DmgTaken = villager_actor->TakeDamage(10, FDamageEvent(), this, villager_actor); 
		}
	}*/

	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	if (SelectedActors.Num() > 0){
		
		// TODO(jhieb) this should live in the character portion I think.
		ARTSHUD* RTSHud = Cast<ARTSHUD>(GetHUD());
		check(RTSHud != nullptr);
		current_gold += 1;
		RTSHud->UpdateGoldCount(current_gold);

		current_wood += 5;
		RTSHud->UpdateWoodCount(current_wood);
		
		
		for(int32 i=0; i < SelectedActors.Num(); i++){
			MoveLocation = Hit.Location + FVector(i / 2 * 100, i % 2 * 100, 0);
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedActors[i]->GetController(), MoveLocation);
			//FORCEINLINE void DrawDebugSphere(const UWorld* InWorld, FVector const& Center, float Radius, int32 Segments, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f) {}
			DrawDebugSphere(GetWorld(), MoveLocation, 25.0, 10, FColor::Red, false, 3.0);
		}
	}
}
