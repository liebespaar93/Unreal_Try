// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CPP_TPSCharacter.h"
#include "CPP_TPSCharaterAnim.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_TRY_API UCPP_TPSCharaterAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// Setting Start Actions
	virtual void NativeInitializeAnimation() override;

	// Setting Update Actions
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	// Owner Character
	ACPP_TPSCharacter* Owner;

	// Forward Backward
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float fVertical;
	// Left Right
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float fHorizontal;

};
