// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectArmy.h"
#include "Engine/Engine.h"


void USelectArmy::Init(int nbOfArmy)
{
	myGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (!myGameInstance)
		return;
	myGameInstance->nbOfPlayers = nbOfArmy;
	for (int i = 0; i < nbOfArmy; i++)
	{
		myGameInstance->Armies.Add(FTypeSoldiers());
	}
}

bool USelectArmy::CanAddNewUnit(int IndexOfPlayer)
{
	int nbUnit = 0;

	nbUnit += myGameInstance->Armies[IndexOfPlayer].Swordman;
	return (nbUnit < nbMaxOfUnit);
}

int USelectArmy::AddNewUnit(TypeOfSoldier type, int IndexOfPlayer)
{
	if (!myGameInstance)
		myGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	switch (type)
	{
	case Swordman:
		if (CanAddNewUnit(IndexOfPlayer))
		{
			myGameInstance->Armies[IndexOfPlayer].Swordman++;
			myGameInstance->Armies[IndexOfPlayer].length++;
		}
		return(myGameInstance->Armies[IndexOfPlayer].Swordman);
		break;
	default:
		break;
	}
	return -1;
}