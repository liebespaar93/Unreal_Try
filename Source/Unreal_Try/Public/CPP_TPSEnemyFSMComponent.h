// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/ActorComponent.h"
#include "CPP_TPSEnemyFSMComponent.generated.h"

UENUM(BlueprintType)
enum class ETPSEnemyState : uint8
{
	IDLE,
	MOVE,
	ATTACK,
	DEAD
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_TRY_API UCPP_TPSEnemyFSMComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPP_TPSEnemyFSMComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY()
	class ACPP_TPSEnemy * Owner;

	// State Of Enemy
	UPROPERTY(BlueprintReadOnly)
	ETPSEnemyState eEnemyState = ETPSEnemyState::IDLE;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxHp=3;
	float Hp;

	void SetState(ETPSEnemyState state);


	// anim

	UPROPERTY()
	class UCPP_TPSEnemyAnim* anim; // 만들어야 함 공격과 이동 등 동작


	// Target Info
	class ACharacter* Target;


	// Action

	void ActionIdle(const float DeltaTime);

	void ActionMove(const float DeltaTime);

	void ActionAttack(const float DeltaTime);
	
	void ActionDead(const float DeltaTime);


	UFUNCTION(BlueprintCallable)
	void OnMyTakeDamage(float value = 1);


	UFUNCTION(BlueprintCallable)
	void OnMyEndAttack(float value = 1);

};
