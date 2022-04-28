// Baudouin Lapeze


#include "MyLevelBattle.h"
#include "HeroesOfLibertyCharacter.h"
#include "ScriptDelegates.h"
#include "Kismet/GameplayStatics.h"

void AMyLevelBattle::Initialize(TArray<FTypeSoldiers> _Armies, TArray<AActor*> _Spawner)
{
	Armies = _Armies;
	Spawners = _Spawner;
	nbSpawn = Armies.Num();
	for (int i = 0; i < nbSpawn; i++)
	{
		SpawnAllSwordmen(Armies[i].Swordman, i, 10);
	}
}

void AMyLevelBattle::SpawnAllSwordmen(int nbSquadron, int indexPlayer, int nbToSpawn)
{
	UWorld * w = GetWorld();
	SpawnLocation = Spawners[indexPlayer]->GetActorLocation();
	int sizeBetween2Unit = 100;
	for (int i = 0; i < nbSquadron; i++)
	{
		ASquadronManager *newSquadron = w->SpawnActor<ASquadronManager>(SquadronToSpawn, SpawnLocation + FVector(0.0f, 0.0f, 120.0f * nbToSpawn + 400.f), FRotator::ZeroRotator);
		newSquadron->SetIndexPlayer(indexPlayer);
		newSquadron->SpawnUnitsBP(nbToSpawn, ActorToSpawn->GetDefaultObject<AHeroesOfLibertyCharacter>(), SpawnLocation + FVector(0.f, sizeBetween2Unit * (nbToSpawn / 2) + 1500.f, 600.f) * i);
		newSquadron->FSpawningDelegate.AddUniqueDynamic(this, &AMyLevelBattle::IncSpawners);
	}
}

void AMyLevelBattle::IncSpawners()
{
	if (nbSpawn <= 0)
	{
		RemoveLoader();
	}
	nbSpawn--;
}
