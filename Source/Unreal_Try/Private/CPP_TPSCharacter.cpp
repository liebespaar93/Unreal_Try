// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_TPSCharacter.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include "CPP_TPSCharacterMovementComponent.h"

// Sets default values
ACPP_TPSCharacter::ACPP_TPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Load Character Mesh
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempCharacterSkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	
	if (tempCharacterSkeletalMesh.Succeeded()){
		this->uCharacterSkeletalMesh = tempCharacterSkeletalMesh.Object;
		this->GetMesh()->SetSkeletalMesh(this->uCharacterSkeletalMesh);
		this->GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
		this->GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	}

	// Create SpringArm For Camera
	this->uCameraSpringArmComp = CreateDefaultSubobject<USpringArmComponent>(FName("uCameraSpringArm"));
	this->uCharacterCamearaComp = CreateDefaultSubobject<UCameraComponent>(FName("uCharacterCamearaComp"));

	this->uCameraSpringArmComp->SetupAttachment(this->GetRootComponent());
	this->uCharacterCamearaComp->SetupAttachment(this->uCameraSpringArmComp);

	this->uCameraSpringArmComp->TargetOffset = FVector(0, 30, 70);
	this->uCameraSpringArmComp->SocketOffset = FVector(150, 0, 0);


	// Input Component Setting
	ConstructorHelpers::FObjectFinder<UInputMappingContext> tempInputMappingContext(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Kyoulee/Inputs/IMC_TPSCharacter.IMC_TPSCharacter'"));

	if (tempInputMappingContext.Succeeded()){
		this->InputMapping = tempInputMappingContext.Object;
	}
	MovementComp = CreateDefaultSubobject < UCPP_TPSCharacterMovementComponent>(TEXT("MovementComp"));

}

// Called when the game starts or when spawned
void ACPP_TPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* playerCtr = Cast<APlayerController>(this->Controller);
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(playerCtr->Player);
	if (LocalPlayer) {
		UE_LOG(LogTemp, Display, TEXT("LoaclPlayer Setting "));
		UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (InputSystem) {
			UE_LOG(LogTemp, Display, TEXT("InputSystem Setting "));
			if (!this->InputMapping.IsNull()) {
				UE_LOG(LogTemp, Display, TEXT("InputMapping Setting "));
				InputSystem->AddMappingContext(this->InputMapping.LoadSynchronous(), 0);
			}
		}
	}
}

// Called every frame
void ACPP_TPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_TPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (nullptr == Input)
		return;

	UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent"));
	this->EnhancedInputComp = Input;
	//InputBindingDelegate.Broadcast(Input);
}

