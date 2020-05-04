// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ObjectMacros.h"
#include "FSoldier.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */




UCLASS()
class HEROESOFLIBERTY_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public :
		UPROPERTY()
		TArray<FTypeSoldiers> Armies;
		int nbOfPlayers = 0;

		UFUNCTION(BlueprintCallable)
			bool CanLaunchGame();
		UFUNCTION(BlueprintCallable)
			TArray<FTypeSoldiers>  GetArmies() { return Armies; };
};
