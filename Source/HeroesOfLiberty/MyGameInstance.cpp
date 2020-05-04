// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

bool UMyGameInstance::CanLaunchGame()
{
	for (int i = 0; i < Armies.Num(); i++)
	{
		if (Armies[i].length == 0)
			return (false);
	}
	return (true);
}
