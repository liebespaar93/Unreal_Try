// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_TPSCharacterGunComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/ChildActorComponent.h"
UCPP_TPSCharacterGunComponent::UCPP_TPSCharacterGunComponent()
{
	this->FireArrow = CreateDefaultSubobject<UArrowComponent>(FName("FireArrow"));
	this->uGunChildActor = CreateDefaultSubobject<UChildActorComponent>(FName("uGunChildActor"));

	ConstructorHelpers::FObjectFinder<UInputAction> tempInputFire(TEXT("/Script/EnhancedInput.InputAction'/Game/Kyoulee/Inputs/Actions/IA_TPSFire.IA_TPSFire'"));
	if (tempInputFire.Succeeded()) {
		this->uIA_Fire = tempInputFire.Object;
	}
}

void UCPP_TPSCharacterGunComponent::InitializeComponent()
{
	Super::InitializeComponent();

	USkeletalMeshComponent* mesh = this->Owner->GetMesh();
	
	if (this->tSpawnWeapon)
	{
		UE_LOG(LogTemp, Display, TEXT("Load Gun"));
		this->aGunActor = GetWorld()->SpawnActor<AActor>(tSpawnWeapon, mesh->GetSocketTransform(FName("ik_hand_gun")));
		this->aGunActor->AttachToComponent(mesh, FAttachmentTransformRules::KeepRelativeTransform, FName("ik_hand_gun"));
		this->aGunActor->SetActorRelativeLocation(FVector(0, 0, 0));
	}
	

}

void UCPP_TPSCharacterGunComponent::BeginPlay()
{
	Super::BeginPlay();
	if (this->Owner)
	{
		this->SetupOwnerInputBinding(this->Owner->EnhancedInputComp);
	}
}

void UCPP_TPSCharacterGunComponent::SetupOwnerInputBinding(UEnhancedInputComponent* EnhancedInputComp)
{
	UE_LOG(LogTemp, Warning, TEXT("SetupOwnerInputBinding"));
	EnhancedInputComp->BindAction(this->uIA_Fire, ETriggerEvent::Triggered, this, &UCPP_TPSCharacterGunComponent::OnInputCharacterFire);

}

void UCPP_TPSCharacterGunComponent::OnInputCharacterFire(const FInputActionInstance& Instance)
{
	UE_LOG(LogTemp, Display, TEXT("OnInputCharacterFire"));

	if (eGunMode == EGun::BallGun)
	{
		FRotator bulletRT = this->aGunActor->GetActorRotation();
		bulletRT = bulletRT + FRotator(0, 90, 0);
		FVector  bulletLC = (bulletRT.Vector() * 100) + this->aGunActor->GetActorLocation();

		AActor* bullet = GetWorld()->SpawnActor<AActor>(tSpawnBullet, bulletLC, bulletRT);
	}
	else if (eGunMode == EGun::ShootingGun)
	{
		FHitResult Hit; // Stores the Hit-Result from the first blocking hit
		// Getting the Forward Vector, where the Actor is currently facing
		// and multipling it by 1000 units along the axis to define the End Point
		FVector Forward = this->Owner->uCharacterCamearaComp->GetForwardVector() * 1000.f;
		// Get the Actors Location which will be our Starting point for the Trace
		FVector Start = this->aGunActor->GetActorLocation();
		FVector End = Start + Forward; // Combine both to have the full LineTrace
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this->Owner);
		CollisionParams.AddIgnoredActor(this->aGunActor);

		if (this->Owner->Controller != nullptr) //check if the Controller is not null
			// Call the LineTrace Function and provide the parameters we just defined
			GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, CollisionParams);
		// To vizualize the LineTrace in-game, lets also draw a DebugLine:
		DrawDebugLine(GetWorld(), Start, End, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 1.0f, 10.0f);

		// Check if something got hit and if the Actor is Valid
		// You can also check for specific Actors e.g.:
		// if (Hit.bBlockingHit && IsValid(Hit.GetActor()) && Hit.GetActor().IsA(AEnemy::StaticClass()))
		if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
		{
			// Do something with the Actor here
			// Example:
			UStaticMeshComponent* aSomeComp = Cast<UStaticMeshComponent>(Hit.GetActor()->GetRootComponent());
			if (aSomeComp)
			{
				aSomeComp->AddImpulse(this->Owner->uCharacterCamearaComp->GetForwardVector() * 1000.f * aSomeComp->GetMass());
			}
		}
		else
		{
			// if no actor got hit, you can do something here 
			// or just Log that nothing got got
			UE_LOG(LogTemp, Log, TEXT("No Actor got got"));
		}
	}

}
