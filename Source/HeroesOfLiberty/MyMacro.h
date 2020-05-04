// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyMacro.generated.h"

/**
 * 
 */
#define PRINT_UNREALINT(value) (GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("%i"), value)))
#define PRINT_UNREALFLOAT(value) (GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("%f"), value)))
#define PRINT_UNREALSTRING(value) (GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, value))

UCLASS()
class HEROESOFLIBERTY_API UMyMacro : public UObject
{
	GENERATED_BODY()
	
};
