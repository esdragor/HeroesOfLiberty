// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SquadronManager.h"
#include "HeroesOfLibertyCharacter.generated.h"

UCLASS(Blueprintable)
class AHeroesOfLibertyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AHeroesOfLibertyCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UStaticMeshComponent* GetCursorToWorld() { return CursorToWorld; }

	UPROPERTY()
		bool authority = false;
	UPROPERTY(VisibleAnywhere)
		int IndexPlayer = 0;
	void SetSelected();
	void SetDeselected();
	UFUNCTION(BlueprintCallable)
		bool GetAuthority() { return authority; }
	UFUNCTION(BlueprintCallable)
		void SetAuthority(bool _auth) { authority = _auth; }
	UFUNCTION(BlueprintCallable)
		void AddTargetEndOverlap(AActor *actorEnd);
	UFUNCTION(BlueprintCallable)
		void DeleteTargetEndOverlap(AActor *actorEnd);
	UFUNCTION(BlueprintCallable)
		float getHealthPercent();
	UPROPERTY(EditAnywhere)
		ASquadronManager *squadron;

protected:

	UPROPERTY(EditInstanceOnly)
		int MaxlifePoint = 15;
	UPROPERTY(EditInstanceOnly)
		int lifePoint = MaxlifePoint;
	UPROPERTY(EditInstanceOnly)
		int Atk_value = 18;
	UPROPERTY(EditInstanceOnly)
		int Def_value = 10;
	UPROPERTY(EditInstanceOnly)
		int Accuracy_value = 10;
	UPROPERTY(EditInstanceOnly)
		int Speed_value = 12;
	UPROPERTY(EditInstanceOnly)
		float maxSpeedAttack = (float)Speed_value / 12.f;
	UPROPERTY(EditInstanceOnly)
		float currentSpeedAttack = maxSpeedAttack;




	UPROPERTY(EditInstanceOnly)
		AHeroesOfLibertyCharacter *target = nullptr;

	bool TakeAHit(int Atk_ennemy);
	UFUNCTION(BlueprintImplementableEvent)
	bool TakeAHitBP();
	void Death();

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* CursorToWorld;

	//virtual void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};

