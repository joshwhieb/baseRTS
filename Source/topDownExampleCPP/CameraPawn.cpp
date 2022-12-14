// excellent man here bailed me out - https://www.youtube.com/watch?v=6JAuSV4WZuc

#include "CameraPawn.h"

#include "Camera/CameraComponent.h"
//#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneComponent.h"


// Sets default values
ACameraPawn::ACameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = currentSpringArmLength;
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetRelativeRotation(FRotator(-60, 0, 0));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<APlayerController>(GetController());
	PC->GetViewportSize(ScreenSizeX, ScreenSizeY);
	
}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PanMoveCamera();

	FVector MoveInputKeys = FVector(0,0,0);
	
	if(bMoveUp){
		MoveInputKeys.X += CamSpeed;
		//AddActorWorldOffset(FVector(CamSpeed,0,0));
	}

	if(bMoveDown){
		MoveInputKeys.X -= CamSpeed;
	}

	if(bMoveRight){
		MoveInputKeys.Y += CamSpeed;
	}

	if (bMoveLeft){
		MoveInputKeys.Y -= CamSpeed;
	}

	if(MoveInputKeys != FVector::ZeroVector){
		AddActorWorldOffset(MoveInputKeys);
	}

}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("MoveUp"), EInputEvent::IE_Pressed, this, &ACameraPawn::MoveUp);
	PlayerInputComponent->BindAction(TEXT("MoveUp"), EInputEvent::IE_Released, this, &ACameraPawn::StopMoveUp);

	PlayerInputComponent->BindAction(TEXT("MoveDown"), EInputEvent::IE_Pressed, this, &ACameraPawn::MoveDown);
	PlayerInputComponent->BindAction(TEXT("MoveDown"), EInputEvent::IE_Released, this, &ACameraPawn::StopMoveDown);

	PlayerInputComponent->BindAction(TEXT("MoveLeft"), EInputEvent::IE_Pressed, this, &ACameraPawn::MoveLeft);
	PlayerInputComponent->BindAction(TEXT("MoveLeft"), EInputEvent::IE_Released, this, &ACameraPawn::StopMoveLeft);

	PlayerInputComponent->BindAction(TEXT("MoveRight"), EInputEvent::IE_Pressed, this, &ACameraPawn::MoveRight);
	PlayerInputComponent->BindAction(TEXT("MoveRight"), EInputEvent::IE_Released, this, &ACameraPawn::StopMoveRight);



	// Scroll wheel and updating the spring arm length.  MouseWheelUp
	PlayerInputComponent->BindAction(TEXT("MouseWheelUp"), EInputEvent::IE_Pressed, this, &ACameraPawn::ZoomIn);
	PlayerInputComponent->BindAction(TEXT("MouseWheelDown"), EInputEvent::IE_Pressed, this, &ACameraPawn::ZoomOut);
}


void ACameraPawn::ZoomIn(){

	if(currentSpringArmLength > SpringArmMinLength){
		currentSpringArmLength -= SpringArmZoomSpeed;
		SpringArm->TargetArmLength = currentSpringArmLength;
	}

}

void ACameraPawn::ZoomOut(){

	if(currentSpringArmLength < SpringArmMaxLength){
		currentSpringArmLength += SpringArmZoomSpeed;
		SpringArm->TargetArmLength = currentSpringArmLength;
	}
}

void ACameraPawn::StopMoveUp(){
	bMoveUp = false;
}

void ACameraPawn::MoveUp(){
	bMoveUp = true;
}


void ACameraPawn::StopMoveDown(){
	bMoveDown = false;
}

void ACameraPawn::MoveDown(){
	bMoveDown = true;
}


void ACameraPawn::StopMoveLeft(){
	bMoveLeft = false;
}

void ACameraPawn::MoveLeft(){
	bMoveLeft = true;
}



void ACameraPawn::StopMoveRight(){
	bMoveRight = false;
}

void ACameraPawn::MoveRight(){
	bMoveRight = true;
}


FVector ACameraPawn::GetCameraPanDirection(){

	float MousePosX;
	float MousePosY;
	float CamDirectionX = 0;
	float CamDirectionY = 0;
	
	PC->GetMousePosition(MousePosX, MousePosY);

	//UE_LOG(LogTemp, Warning, TEXT("MousePosition %s"), *FVector(MousePosX, MousePosY, 0).ToString());

	if(MousePosX <= Margin){
		CamDirectionY = -CamSpeed;
	} else if (MousePosX >= ScreenSizeX - Margin ){
		CamDirectionY = CamSpeed;
	}

	if(MousePosY <= Margin){
		CamDirectionX = CamSpeed;
	} else if (MousePosY >= ScreenSizeY - Margin){
		CamDirectionX = -CamSpeed;
	}


	//UE_LOG(LogTemp, Warning, TEXT("pan direction %s"), *FVector(CamDirectionX, CamDirectionY, 0).ToString());

	return FVector(CamDirectionX, CamDirectionY, 0);

}

void ACameraPawn::PanMoveCamera(){
	FVector panDirection = GetCameraPanDirection();

	if(panDirection == FVector::ZeroVector){
		return;
	} else {
		AddActorWorldOffset(panDirection);
	}
}

