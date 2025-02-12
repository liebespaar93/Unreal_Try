// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPP_TPSEnemy.generated.h"

UCLASS()
class UNREAL_TRY_API ACPP_TPSEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_TPSEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	USkeletalMesh* uCharacterSkeletalMesh;

	// Components
	UPROPERTY(EditDefaultsOnly)
	class UCPP_TPSEnemyFSMComponent* EnemyFSMComp;

	class UCPP_TPSEnemyAnim* EnemyAnim;
};
