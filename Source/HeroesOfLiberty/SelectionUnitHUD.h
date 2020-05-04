// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameFramework/PlayerController.h"
#include "HeroesOfLibertyCharacter.h"
#include "SelectionUnitHUD.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFLIBERTY_API ASelectionUnitHUD : public AHUD
{
	GENERATED_BODY()
	
public :
	FVector2D StartSelectionSquare;
	FVector2D CurrentSelectionSquare;
	bool onSelection = false;
	APlayerController *PC;
	TArray<AHeroesOfLibertyCharacter *> TmpSelection;
	TArray<AHeroesOfLibertyCharacter*> UnitSelection;

	FVector2D GetMousePosOnScreen();
	virtual void DrawHUD() override;
	void UnitsSelected();
	void GetUnitsDeselected();
	void SelectSquadron(int index);


};
