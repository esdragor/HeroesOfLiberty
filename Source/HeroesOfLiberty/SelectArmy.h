// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyGameInstance.h"
#include "SelectArmy.generated.h"

/**
 *
 */

UENUM(BlueprintType)
enum TypeOfSoldier
{
	Swordman
};

UCLASS()
class HEROESOFLIBERTY_API USelectArmy : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY()
		int nbMaxOfUnit = 6;

	UPROPERTY()
		UMyGameInstance * myGameInstance;

	UFUNCTION(BlueprintCallable)
		void Init(int nbOfArmy);

	UFUNCTION(BlueprintCallable)
		int AddNewUnit(TypeOfSoldier type, int IndexOfPlayer);

	UFUNCTION()
		bool CanAddNewUnit(int IndexOfPlayer);

};
