// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

UCLASS()
class TOPDOWNEXAMPLECPP_API ACameraPawn : public APawn
{
	GENERATED_BODY()

private:

	int currentSpringArmLength = 1200;
	APlayerController* PC;
	int SpringArmMaxLength = 5000;
	int SpringArmMinLength = 0;
	int SpringArmZoomSpeed = 1000;
	bool bMoveUp = false;
	bool bMoveDown = false;
	bool bMoveLeft = false;
	bool bMoveRight = false;

	UPROPERTY()
	float CamSpeed = 10;

	UPROPERTY()
	int32 ScreenSizeX;

	UPROPERTY()
	int32 ScreenSizeY;

	UPROPERTY()
	float Margin = 50;

	// Arrow key functions.
	void MoveUp();
	void StopMoveUp();
	void MoveDown();
	void StopMoveDown();
	void MoveLeft();
	void StopMoveLeft();
	void MoveRight();
	void StopMoveRight();
	
	FVector GetCameraPanDirection();
	void PanMoveCamera();
	void ZoomIn();
	void ZoomOut();

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

