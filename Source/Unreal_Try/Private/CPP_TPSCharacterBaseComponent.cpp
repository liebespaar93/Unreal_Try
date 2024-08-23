// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_TPSCharacterBaseComponent.h"


// Sets default values for this component's properties
UCPP_TPSCharacterBaseComponent::UCPP_TPSCharacterBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}

// Called when the game starts
void UCPP_TPSCharacterBaseComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UCPP_TPSCharacterBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCPP_TPSCharacterBaseComponent::InitializeComponent()
{
	Super::InitializeComponent();

	UE_LOG(LogTemp, Display, TEXT("UCPP_TPSCharacterBaseComponent InitializeComponent Setting "));
	this->Owner = Cast<ACPP_TPSCharacter>(GetOwner());
}

void UCPP_TPSCharacterBaseComponent::SetupOwnerInputBinding(UEnhancedInputComponent* EnhancedInputComp)
{
}
