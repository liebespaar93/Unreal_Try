// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_TPSEnemy.h"

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

	
}

// Called when the game starts or when spawned
void ACPP_TPSEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_TPSEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_TPSEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

