// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectMacros.h"
#include "FSoldier.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FTypeSoldiers
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		int Swordman = 0;
	UPROPERTY(BlueprintReadOnly)
		int length = 0;

	FTypeSoldiers()
	{
		Swordman = 0;
		length = 0;
	}
};

UCLASS()
class HEROESOFLIBERTY_API UFSoldier : public UObject
{
	GENERATED_BODY()

public:
	UFSoldier();
	~UFSoldier();
};
