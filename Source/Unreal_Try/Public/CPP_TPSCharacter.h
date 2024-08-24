// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "InputMappingContext.h"
#include "CPP_TPSCharacter.generated.h"


//DECLARE_MULTICAST_DELEGATE_OneParam(FInputBindingDelegate, class UEnhancedInputComponent*)

UCLASS()
class UNREAL_TRY_API ACPP_TPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_TPSCharacter();

	//FInputBindingDelegate InputBindingDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	USkeletalMesh* uCharacterSkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* uCameraSpringArmComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* uCharacterCamearaComp;

	//input Control
	class UEnhancedInputComponent* EnhancedInputComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UInputMappingContext> InputMapping;

	// Components
	UPROPERTY(EditDefaultsOnly)
	class UCPP_TPSCharacterMovementComponent* MovementComp;

	UPROPERTY(EditDefaultsOnly)
	class UCPP_TPSCharacterGunComponent* GunComp;


};
