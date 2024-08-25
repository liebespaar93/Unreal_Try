// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CPP_TPSEnemyFSMComponent.h"
#include "CPP_TPSEnemyAnim.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_TRY_API UCPP_TPSEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	// Setting Start Actions
	virtual void NativeInitializeAnimation() override;

	// Setting Update Actions
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// Owner Character
	class ACPP_TPSEnemy* Owner;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	ETPSEnemyState state;

	bool bAttack = false;

	UFUNCTION()
	void AnimNotify_AttackStart();

	UFUNCTION()
	void AnimNotify_AttackEnd();


};
