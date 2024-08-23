// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <EnhancedInputComponent.h>
#include "CPP_TPSCharacter.h"
#include "CPP_TPSCharacterBaseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_TRY_API UCPP_TPSCharacterBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPP_TPSCharacterBaseComponent();


protected:
	virtual void InitializeComponent() override;
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupOwnerInputBinding(UEnhancedInputComponent* EnhancedInputComp);

	class ACPP_TPSCharacter* Owner;
};
