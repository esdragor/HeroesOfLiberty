// Baudouin Lapeze


#include "SquadronManager.h"
#include "HeroesOfLibertyCharacter.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
ASquadronManager::ASquadronManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	w = GetWorld();
}

// Called when the game starts or when spawned
void ASquadronManager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASquadronManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASquadronManager::SpawnUnit(int nb, UClass *_objToSpawn, FVector pos)
{
	objToSpawn = _objToSpawn;
	FVector SpawnLocation = pos;
	for (int i = 0; i < nb; i++)
	{
		if (i > nb / 2)
		{
			SpawnLocation.X -= 120.f;
			SpawnLocation.Y -= 120 * (i / 2 + 1);
		}
		SpawnNewUnitDelay(SpawnLocation);
		SpawnLocation.Y += 120;
	}
	SpawnLocation = pos;
	for (int i = 0; i < nb; i++)
	{
		if (i > nb / 2)
		{
			SpawnLocation.X -= 120.f;
			SpawnLocation.Y -= 120 * (i + 1);
		}

		//SpawnNewUnitDelay(newSpawnLoc);

		SpawnLocation.Y += 120;
	}
}

void ASquadronManager::Spawn(FVector pos)
{
	GetWorld()->SpawnActor<ASquadronManager>(GetClass(), pos, FRotator::ZeroRotator);
}

FVector ASquadronManager::UpdateSpawnPos(int cpt, int maxSpawn, FVector pos)
{
	if (cpt == maxSpawn / 2)
	{
		pos.X -= 120.f;
		pos.Y -= 120 * (maxSpawn / 2);
	}
	pos.Y += 120;
	return pos;
}

void ASquadronManager::SetValueNewSoldier(AHeroesOfLibertyCharacter *NSoldier)
{
	NSoldier->squadron = this;
	NSoldier->IndexPlayer = IndexPlayer;
	if (IndexPlayer == 0)
	{
		NSoldier->SetAuthority(true);

	}
	units.Add(NSoldier);
}

void ASquadronManager::SpawnNewUnitDelay(FVector SpawnLocation)
{
	FActorSpawnParameters param;
	AHeroesOfLibertyCharacter *newUnit = w->SpawnActor<AHeroesOfLibertyCharacter>(objToSpawn, SpawnLocation, FRotator::ZeroRotator);
	if (newUnit)
	{
		newUnit->squadron = this;
		newUnit->IndexPlayer = IndexPlayer;
		if (IndexPlayer == 0)
		{
			newUnit->SetAuthority(true);

		}
		units.Add(newUnit);
	}
}

void ASquadronManager::FinishSpawningSoldier()
{
	FSpawningDelegate.Broadcast();
}

