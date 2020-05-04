// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CameraPawn.h"
#include "HeroesOfLibertyCharacter.h"
#include "HeroesOfLibertyPlayerController.generated.h"

class CameraPawn;
class ASelectionUnitHUD;

UCLASS()
class AHeroesOfLibertyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AHeroesOfLibertyPlayerController();
	void SelectUnitsEnd();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;
	uint32 SpeedZoom = 90;

	ASelectionUnitHUD *HUDSelection;

	TArray<AHeroesOfLibertyCharacter *> UnitsSelected;

	// Begin PlayerController interface
	void BeginPlay();
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	// End PlayerController interface

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	void ZoomIn();
	void ZoomOut();

	void SelectUnitsBegin();
	void MoveUnitsSelected();

};


