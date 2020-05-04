// Baudouin Lapeze

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SquadronManager.generated.h"

class AHeroesOfLibertyCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFinishSpawning);


UCLASS()
class HEROESOFLIBERTY_API ASquadronManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASquadronManager();
	TArray<AHeroesOfLibertyCharacter*> *GetUnits() { return &units; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY()
		TArray<AHeroesOfLibertyCharacter*> units;
	UPROPERTY()
		TSubclassOf<class AHeroesOfLibertyCharacter> ActorToSpawn;
	UPROPERTY()
		int IndexPlayer = 0;
	UWorld *w;
	UClass *objToSpawn;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
		void SpawnUnit(int nb, UClass *objToSpawn, FVector pos);
	UFUNCTION(BlueprintCallable)
		void Spawn(FVector pos);
		UFUNCTION(BlueprintCallable)
		FVector UpdateSpawnPos(int cpt, int maxSpawn, FVector pos);
		UFUNCTION(BlueprintCallable)
			void SetValueNewSoldier(AHeroesOfLibertyCharacter *NSoldier);
	UFUNCTION(BlueprintImplementableEvent)
		void SpawnUnitsBP(int nb, AHeroesOfLibertyCharacter *objToSpawn, FVector pos);

	int GetIndexPlayer() const { return IndexPlayer; }
	void SetIndexPlayer(int val) { IndexPlayer = val; }

	void SpawnNewUnitDelay(FVector SpawnLocation);

	FFinishSpawning FSpawningDelegate;

	UFUNCTION(BlueprintCallable)
		void FinishSpawningSoldier();
};
