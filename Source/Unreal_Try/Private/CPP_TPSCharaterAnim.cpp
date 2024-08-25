// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_TPSCharaterAnim.h"

void UCPP_TPSCharaterAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	this->Owner = Cast<ACPP_TPSCharacter>(this->TryGetPawnOwner());
}

void UCPP_TPSCharaterAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Owner)
		return;
	FVector velocity = this->Owner->GetVelocity();

	this->fVertical = FVector::DotProduct( this->Owner->GetActorForwardVector(), velocity);
	this->fHorizontal = FVector::DotProduct(this->Owner->GetActorRightVector(), velocity);
}
