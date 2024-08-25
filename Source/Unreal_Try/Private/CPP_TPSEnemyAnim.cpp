// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_TPSEnemyAnim.h"
#include "CPP_TPSEnemy.h"
#include "CPP_TPSEnemyFSMComponent.h"

void UCPP_TPSEnemyAnim::NativeInitializeAnimation()
{

	Super::NativeInitializeAnimation();

	this->Owner = Cast<ACPP_TPSEnemy>(this->TryGetPawnOwner());
}

void UCPP_TPSEnemyAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Owner)
		return;
}

void UCPP_TPSEnemyAnim::AnimNotify_AttackStart()
{
	this->bAttack = true;
}

void UCPP_TPSEnemyAnim::AnimNotify_AttackEnd()
{
	this->bAttack = false;
	UCPP_TPSEnemyFSMComponent* enemyFSM = Owner->GetComponentByClass<UCPP_TPSEnemyFSMComponent>();
	enemyFSM->OnMyEndAttack();
}

