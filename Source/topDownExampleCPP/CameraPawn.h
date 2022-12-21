// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

UCLASS()
class TOPDOWNEXAMPLECPP_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int currentSpringArmLength = 1200;
	int SpringArmMaxLength = 2400;
	int SpringArmMinLength = 300;
	int SpringArmZoomSpeed = 100;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;


	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	APlayerController* PC;

	UFUNCTION()
	FVector GetCameraPanDirection();

	UFUNCTION()
	void PanMoveCamera();

	UPROPERTY()
	float Margin = 100;

	UPROPERTY()
	int32 ScreenSizeX;

	UPROPERTY()
	int32 ScreenSizeY;

	UPROPERTY()
	float CamSpeed = 10;

	void MoveUp();
	void StopMoveUp();
	bool bMoveUp = false;

	void MoveDown();
	void StopMoveDown();
	bool bMoveDown = false;

	void MoveLeft();
	void StopMoveLeft();
	bool bMoveLeft = false;

	void MoveRight();
	void StopMoveRight();
	bool bMoveRight = false;

	void ZoomIn();
	void ZoomOut();

};

