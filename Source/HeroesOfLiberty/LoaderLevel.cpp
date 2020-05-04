// Baudouin Lapeze


#include "LoaderLevel.h"
#include "Paths.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"


void ALoaderLevel::BeginPlay()
{
	Super::BeginPlay();
}

void ALoaderLevel::LoadLevelStream()
{
	if (LevelToLoad != "")
	{
		FLatentActionInfo LatentInfo;
		UGameplayStatics::LoadStreamLevel(this, LevelToLoad, true, true, LatentInfo);
	}
}