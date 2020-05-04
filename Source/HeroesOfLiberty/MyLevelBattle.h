// Baudouin Lapeze

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "SelectArmy.h"
#include "SquadronManager.h"
#include "CameraPawn.h"
#include "MyLevelBattle.generated.h"
/**
 *
 */
UCLASS()
class HEROESOFLIBERTY_API AMyLevelBattle : public ALevelScriptActor
{
	GENERATED_BODY()
public:
		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FTypeSoldiers> Armies;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<AActor*> Spawners;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class AHeroesOfLibertyCharacter> ActorToSpawn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class ASquadronManager> SquadronToSpawn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class ACameraPawn> CameraToSpawn;
	UPROPERTY()
		FVector SpawnLocation;
	UPROPERTY(EditAnywhere)
		int nbSpawn = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UUserWidget *LoaderWidget;

protected:
	UFUNCTION(BlueprintCallable)
		void Initialize(TArray<FTypeSoldiers> _Armies, TArray<AActor*> _Spawner);

	UFUNCTION()
		void SpawnAllSwordmen(int nbUnit, int indexPlayer);

	UFUNCTION()
		void IncSpawners();
	UFUNCTION(BlueprintImplementableEvent)
		void RemoveLoader();

	int nbToSpawn = 100;

};
