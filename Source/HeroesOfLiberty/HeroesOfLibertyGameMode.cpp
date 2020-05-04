// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "HeroesOfLibertyGameMode.h"
#include "HeroesOfLibertyPlayerController.h"
#include "HeroesOfLibertyCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "SelectionUnitHUD.h"

AHeroesOfLibertyGameMode::AHeroesOfLibertyGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AHeroesOfLibertyPlayerController::StaticClass();

	HUDClass = ASelectionUnitHUD::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MyCameraPawn"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}