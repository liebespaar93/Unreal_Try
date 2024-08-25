// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_TPSCharacterBaseComponent.h"
#include "CPP_TPSCharacterGunComponent.generated.h"


enum class EGun
{
	BallGun,
	ShootingGun
};

/**
 * 
 */
UCLASS()
class UNREAL_TRY_API UCPP_TPSCharacterGunComponent : public UCPP_TPSCharacterBaseComponent
{
	GENERATED_BODY()

public:
	UCPP_TPSCharacterGunComponent();

private:
	EGun eGunMode = EGun::ShootingGun;

protected:
	virtual void InitializeComponent() override;

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun")
	TSubclassOf<AActor> tSpawnWeapon;
	AActor* aGunActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun")
	TSubclassOf<AActor> tSpawnBullet;

	UPROPERTY()
	class UChildActorComponent* uGunChildActor;

	UPROPERTY()
	class UArrowComponent* FireArrow;

	virtual void SetupOwnerInputBinding(UEnhancedInputComponent* EnhancedInputComp) override;

	UPROPERTY(EditAnywhere, Category = "Enhanced Inputs")
	UInputAction* uIA_Fire;

	UFUNCTION()
	void OnInputCharacterFire(const FInputActionInstance& Instance);

};
