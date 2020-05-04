// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "HeroesOfLibertyPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "HeroesOfLibertyCharacter.h"
#include "UObject/UObjectGlobals.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"
#include "AI/NavigationSystemBase.h"
#include "SelectionUnitHUD.h"

AHeroesOfLibertyPlayerController::AHeroesOfLibertyPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AHeroesOfLibertyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUDSelection = Cast<ASelectionUnitHUD>(GetHUD());
}

void AHeroesOfLibertyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void AHeroesOfLibertyPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AHeroesOfLibertyPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AHeroesOfLibertyPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AHeroesOfLibertyPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AHeroesOfLibertyPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &AHeroesOfLibertyPlayerController::OnResetVR);
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &AHeroesOfLibertyPlayerController::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &AHeroesOfLibertyPlayerController::ZoomOut);


	InputComponent->BindAction("LeftMouse", IE_Pressed, this, &AHeroesOfLibertyPlayerController::SelectUnitsBegin);
	InputComponent->BindAction("LeftMouse", IE_Released, this, &AHeroesOfLibertyPlayerController::SelectUnitsEnd);
	InputComponent->BindAction("RightMouse", IE_Released, this, &AHeroesOfLibertyPlayerController::MoveUnitsSelected);
}

void AHeroesOfLibertyPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AHeroesOfLibertyPlayerController::MoveToMouseCursor()
{

}

void AHeroesOfLibertyPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AHeroesOfLibertyPlayerController::SetNewMoveDestination(const FVector DestLocation)
{

}

void AHeroesOfLibertyPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AHeroesOfLibertyPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}


void AHeroesOfLibertyPlayerController::ZoomIn()
{

	GetPawn()->FindComponentByClass<USpringArmComponent>()->TargetArmLength -= SpeedZoom;
}

void AHeroesOfLibertyPlayerController::ZoomOut()
{

	GetPawn()->FindComponentByClass<USpringArmComponent>()->TargetArmLength += SpeedZoom;
}

void AHeroesOfLibertyPlayerController::SelectUnitsBegin()
{
		HUDSelection->GetUnitsDeselected();
		HUDSelection->StartSelectionSquare = HUDSelection->GetMousePosOnScreen();
		HUDSelection->onSelection = true;
}

void AHeroesOfLibertyPlayerController::SelectUnitsEnd()
{
	if (!HUDSelection)
		HUDSelection = Cast<ASelectionUnitHUD>(GetHUD());
	UnitsSelected = HUDSelection->UnitSelection;

	HUDSelection->onSelection = false;
}

void AHeroesOfLibertyPlayerController::MoveUnitsSelected()
{
	SelectUnitsEnd();
	for (int i = 0; i < UnitsSelected.Num(); i++)
	{
		FHitResult hit;

		GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hit);
		FVector TargetLocation = hit.Location;
		TargetLocation += FVector(i % 2 * 100, i / 2 * 100, 0); //basic formation
		if (UnitsSelected[i])
		{
			AController *controller = UnitsSelected[i]->GetController();
			if (controller)
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(controller, TargetLocation);
		}
	}
}