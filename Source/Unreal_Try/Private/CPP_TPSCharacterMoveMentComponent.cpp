// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_TPSCharacterMoveMentComponent.h"

UCPP_TPSCharacterMovementComponent::UCPP_TPSCharacterMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UInputAction> tempInputMovement(TEXT("/Script/EnhancedInput.InputAction'/Game/Kyoulee/Inputs/Actions/IA_TPSMovement.IA_TPSMovement'"));
	if (tempInputMovement.Succeeded()) {
		this->uIA_Movement = tempInputMovement.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> tempInputLook(TEXT("/Script/EnhancedInput.InputAction'/Game/Kyoulee/Inputs/Actions/IA_TPSLook.IA_TPSLook'"));
	if (tempInputLook.Succeeded()) {
		this->uIA_Look = tempInputLook.Object;
	}

}

void UCPP_TPSCharacterMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();
	UE_LOG(LogTemp, Display, TEXT("CPP_TPSCharacterMoveMentComp InitializeComponent Setting "));
}

void UCPP_TPSCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("UCPP_TPSCharacterMovementComp BeginPlay "));
	
	if (this->Owner)
	{
		this->SetupOwnerInputBinding(this->Owner->EnhancedInputComp);
	}
}

void UCPP_TPSCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	this->Owner->AddMovementInput(this->MovementDir);
}

void UCPP_TPSCharacterMovementComponent::SetupOwnerInputBinding(UEnhancedInputComponent* EnhancedInputComp)
{
	UE_LOG(LogTemp, Display, TEXT("UEnhancedInput BindAction Setting "));
	EnhancedInputComp->BindAction(uIA_Movement, ETriggerEvent::Triggered, this, &UCPP_TPSCharacterMovementComponent::OnInputCharacterMovement);
	EnhancedInputComp->BindAction(uIA_Look, ETriggerEvent::Triggered, this, &UCPP_TPSCharacterMovementComponent::OnInputCharacterLook);
}

void UCPP_TPSCharacterMovementComponent::OnInputCharacterMovement(const FInputActionInstance& Instance)
{
	FVector2D AxisValue2D = Instance.GetValue().Get<FVector2D>();

	this->MovementDir = FVector(AxisValue2D.X, AxisValue2D.Y, 0);
}

void UCPP_TPSCharacterMovementComponent::OnInputCharacterLook(const FInputActionInstance& Instance)
{
	FVector2D AxisValue2D = Instance.GetValue().Get<FVector2D>();

	this->Owner->uCameraSpringArmComp->AddRelativeRotation(FRotator(AxisValue2D.Y, AxisValue2D.X, 0));
	UE_LOG(LogTemp, Display, TEXT("x :%f y : %f"), AxisValue2D.X, AxisValue2D.Y);

}
