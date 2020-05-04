// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraPawn.h"
#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "MyMacro.h"

// Sets default values
ACameraPawn::ACameraPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootScene);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetRelativeRotation(FRotator(-50, 0, 0));
	SpringArm->TargetArmLength = 700;
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArm);
}

void ACameraPawn::WaitInit()
{
	PC = Cast<APlayerController>(GetController());
	PC->GetViewportSize(ScreenSizeX, ScreenSizeY);
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TriggerWaitHandle, this, &ACameraPawn::WaitInit, 1.f, true);


}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorWorldOffset(GetCameraPanDirection() * CamSpeedMove);
}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector ACameraPawn::GetCameraPanDirection()
{
	float MousePosX;
	float MousePosY;
	float CamDirectionX = 0;
	float CamDirectionY = 0;
	FString msg = "";

	if (PC == nullptr || ScreenSizeX == 0 || ScreenSizeY == 0) // not yet initialized
		return FVector(0, 0, 0);

	PC->GetMousePosition(MousePosX, MousePosY);


	if (MousePosX <= margin)
	{
		CamDirectionY = -1;
	}
	if (MousePosY <= margin)
	{
		CamDirectionX = 1;
	}

	if (MousePosX >= ScreenSizeX - margin)
	{
		CamDirectionY = 1;
	}
	if (MousePosY >= ScreenSizeY - margin)
	{
		CamDirectionX = -1;
	}

	return FVector(CamDirectionX, CamDirectionY, 0);
}


void ACameraPawn::ZoomIn()
{
	SpringArm->TargetArmLength -= CamSpeedZoom;
}

void ACameraPawn::ZoomOut()
{
	SpringArm->TargetArmLength += CamSpeedZoom;
}