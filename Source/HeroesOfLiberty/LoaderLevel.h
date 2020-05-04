// Baudouin Lapeze

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Engine/StreamableManager.h"
#include "LoaderLevel.generated.h"

/**
 * 
 */

UCLASS()
class HEROESOFLIBERTY_API ALoaderLevel : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FName LevelToLoad = "";
	UFUNCTION(BlueprintCallable)
		void LoadLevelStream();
protected:

	void BeginPlay() override;


};
