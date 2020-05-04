// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "HeroesOfLibertyCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "SelectionUnitHUD.h"

AHeroesOfLibertyCharacter::AHeroesOfLibertyCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a decal in the world to show the cursor's location

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	CursorToWorld = CreateDefaultSubobject<UStaticMeshComponent>("CursorToWorld");
	CursorToWorld->SetStaticMesh(SphereMeshAsset.Object);
	CursorToWorld->SetupAttachment(RootComponent);
	//static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	//if (DecalMaterialAsset.Succeeded())
	//{
	//	CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	//}
	//CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetWorldScale3D(FVector(0.01f, 1, 1));
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	CursorToWorld->SetRelativeLocation(FVector(0.f, 0.f, -80.f));
	CursorToWorld->SetVisibility(false);


	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AHeroesOfLibertyCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (target)
	{
		currentSpeedAttack -= DeltaSeconds;
		if (currentSpeedAttack <= 0.0f)
		{
			if (rand() % 100 < Accuracy_value)
			if (target->TakeAHit(Atk_value)) //is dead
				target = nullptr;
			currentSpeedAttack = maxSpeedAttack;
		}
	}
}

void AHeroesOfLibertyCharacter::SetSelected()
{
	if(authority)
		CursorToWorld->SetVisibility(true);
}

void AHeroesOfLibertyCharacter::SetDeselected()
{
	CursorToWorld->SetVisibility(false);

}

void AHeroesOfLibertyCharacter::AddTargetEndOverlap(AActor *actorEnd)
{
	if (target == nullptr)
	{
		AHeroesOfLibertyCharacter *enemyBegin = Cast<AHeroesOfLibertyCharacter>(actorEnd);
		if (enemyBegin != nullptr)
			if (enemyBegin->IndexPlayer != IndexPlayer) //different team
			{
				target = enemyBegin;
			}
	}
}

void AHeroesOfLibertyCharacter::DeleteTargetEndOverlap(AActor *actorEnd)
{
	if (target != nullptr)
	{
		AHeroesOfLibertyCharacter *enemyEnd = Cast<AHeroesOfLibertyCharacter>(actorEnd);
		if (enemyEnd != nullptr)
		if (target == enemyEnd)
			target = nullptr;
	}
}

bool AHeroesOfLibertyCharacter::TakeAHit(int Atk_ennemy)
{
	int damage = Atk_ennemy - Def_value;

	if (damage <= 0)
		return false;
	lifePoint -= damage;
	if (lifePoint <= 0)
	{
		Death();
		return (true);
	}
	TakeAHitBP();
	return (false);
}

void AHeroesOfLibertyCharacter::Death()
{
	squadron->GetUnits()->Remove(this);
	
	Cast<ASelectionUnitHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->UnitSelection.Remove(this);
	Destroy();
}

float AHeroesOfLibertyCharacter::getHealthPercent()
{
	return ((float)lifePoint / (float)MaxlifePoint);
}

