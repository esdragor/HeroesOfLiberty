// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "CameraPawn.generated.h"

UCLASS()
class ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
		USceneComponent* RootScene;

	UPROPERTY()
		USpringArmComponent* SpringArm;

	UPROPERTY()
		UCameraComponent* CameraComp;

	UPROPERTY()
		APlayerController* PC;


	UPROPERTY()
		float margin = 15;
	UPROPERTY()
	int32 ScreenSizeX = 0;
	UPROPERTY()
	int32 ScreenSizeY = 0;

	UPROPERTY()
		float CamSpeedZoom = 2400;
	UPROPERTY()
		float CamSpeedMove = 20;
	FTimerHandle TriggerWaitHandle;


	UFUNCTION()
		FVector GetCameraPanDirection();

	UFUNCTION()
		void ZoomIn();

	UFUNCTION()
		void ZoomOut();
	UFUNCTION()
		void WaitInit();
};
