// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_TPSCharacterBaseComponent.h"
#include "CPP_TPSCharacterMoveMentComponent.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_TRY_API UCPP_TPSCharacterMovementComponent : public UCPP_TPSCharacterBaseComponent
{
	GENERATED_BODY()
public:
	UCPP_TPSCharacterMovementComponent();


	// Status
	FVector MovementDir;

protected:
	virtual void InitializeComponent() override;

	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupOwnerInputBinding(UEnhancedInputComponent* EnhancedInputComp) override;

	UPROPERTY(EditAnywhere, Category = "Enhanced Inputs")
	UInputAction* uIA_Movement;

	UFUNCTION()
	void OnInputCharacterMovement(const FInputActionInstance& Instance);

};
