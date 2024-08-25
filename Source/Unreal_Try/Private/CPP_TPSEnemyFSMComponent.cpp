// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_TPSEnemyFSMComponent.h"
#include "CPP_TPSEnemyAnim.h"
#include "CPP_TPSEnemy.h"
#include "CPP_TPSCharacter.h"
#include "AIController.h"

// Sets default values for this component's properties
UCPP_TPSEnemyFSMComponent::UCPP_TPSEnemyFSMComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	// ...
}


// Called when the game starts
void UCPP_TPSEnemyFSMComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	this->Target = GetWorld()->GetFirstPlayerController()->GetCharacter();
	//Cast<AAIController>(this->Owner->GetController());
}

void UCPP_TPSEnemyFSMComponent::InitializeComponent()
{
	Super::InitializeComponent();

	this->Hp = this->MaxHp;
	this->Owner = Cast<ACPP_TPSEnemy>(this->GetOwner());
	anim = Cast< UCPP_TPSEnemyAnim>(this->Owner->GetMesh()->GetAnimInstance());
}


// Called every frame
void UCPP_TPSEnemyFSMComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	switch (this->eEnemyState)
	{
	case ETPSEnemyState::MOVE:
		ActionMove(DeltaTime); break;
	case ETPSEnemyState::ATTACK:
		ActionAttack(DeltaTime); break;
	case ETPSEnemyState::DEAD:
		ActionDead(DeltaTime); break;
	default:
		ActionIdle(DeltaTime); break;
		break;
	}
}

void UCPP_TPSEnemyFSMComponent::SetState(ETPSEnemyState state)
{
	this->eEnemyState = state;
	this->anim->state = this->eEnemyState;
}

void UCPP_TPSEnemyFSMComponent::ActionIdle(const float DeltaTime)
{
	if (Target)
	{
		UE_LOG(LogTemp, Display, TEXT("ActionMove"));
		SetState(ETPSEnemyState::MOVE);
	}

}

void UCPP_TPSEnemyFSMComponent::ActionMove(const float DeltaTime)
{
	if (!Target)
		return;

	FVector moveDir = this->Target->GetActorLocation() - this->Owner->GetActorLocation();

	if (moveDir.Length() < 100)
	{
		UE_LOG(LogTemp, Display, TEXT("ATTACK"));
		SetState(ETPSEnemyState::ATTACK);
		return;
	}

	this->Owner->AddMovementInput(moveDir);

	this->Owner->SetActorRotation(moveDir.Rotation());
}

void UCPP_TPSEnemyFSMComponent::ActionAttack(const float DeltaTime)
{
	FVector Dir = this->Target->GetActorLocation() - this->Owner->GetActorLocation();

	if (this->Owner->EnemyAnim->bAttack)
		return;

	if (Dir.Length() > 100)
	{
		UE_LOG(LogTemp, Display, TEXT("MOVE"));
		SetState(ETPSEnemyState::MOVE);
		return;
	}
}

void UCPP_TPSEnemyFSMComponent::ActionDead(const float DeltaTime)
{
}

void UCPP_TPSEnemyFSMComponent::OnMyTakeDamage(float value)
{
	if (value < 0)
		return;
	this->Hp -= value;
	if (this->Hp <= 0)
	{
		SetState(ETPSEnemyState::DEAD);
	}
}

void UCPP_TPSEnemyFSMComponent::OnMyEndAttack(float value)
{

	if (this->Owner->GetDistanceTo(this->Target) > 200)
		return;
	ACPP_TPSCharacter* tpsTarget = Cast<ACPP_TPSCharacter>(this->Target);

	if (tpsTarget)
		tpsTarget->OnTakeDamage(1);
}

