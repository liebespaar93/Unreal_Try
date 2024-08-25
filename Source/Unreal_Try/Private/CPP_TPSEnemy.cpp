// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_TPSEnemy.h"
#include "CPP_TPSEnemyFSMComponent.h"
#include "CPP_TPSEnemyAnim.h"

// Sets default values
ACPP_TPSEnemy::ACPP_TPSEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Load Character Mesh
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempCharacterSkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Kyoulee/Enemy/Enemy.Enemy'"));

	if (tempCharacterSkeletalMesh.Succeeded()) {
		this->uCharacterSkeletalMesh = tempCharacterSkeletalMesh.Object;
		this->GetMesh()->SetSkeletalMesh(this->uCharacterSkeletalMesh);
		this->GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
		this->GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	}

	/*ConstructorHelpers::FClassFinder<UAnimInstance> tempAnimBP(TEXT("/Script/Engine.AnimBlueprint'/Game/Kyoulee/Enemy/Anim/ABP_Enemy.ABP_Enemy'"));

	if (tempAnimBP.Succeeded())
	{
		this->GetMesh()->SetAnimClass(tempAnimBP.Class);
	}*/

	EnemyFSMComp = CreateDefaultSubobject<UCPP_TPSEnemyFSMComponent>(TEXT("EnemyFSMComp"));
}

// Called when the game starts or when spawned
void ACPP_TPSEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	this->EnemyAnim = Cast<UCPP_TPSEnemyAnim>(this->GetMesh()->GetAnimInstance());
}

// Called every frame
void ACPP_TPSEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
