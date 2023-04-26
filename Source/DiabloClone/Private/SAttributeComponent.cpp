// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"
#include <Math/UnrealMathUtility.h>

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;

	ManaMax = 100.0f;
	Mana = ManaMax;
	HealthMax = 100.0f;
	Health = HealthMax;
	MeleeAttackRange = 300.0f;
}



// Called when the game starts
void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


float USAttributeComponent::GetHealth()
{
	return Health;
}

float USAttributeComponent::GetHealthMax()
{
	return HealthMax;
}

float USAttributeComponent::GetMana()
{
	return Mana;
}

float USAttributeComponent::GetManaMax()
{
	return ManaMax;
}

void USAttributeComponent::ApplyHealtChange(float Value)
{
	float NewHealth = FMath::Clamp(Health + Value, 0.0f, HealthMax);
	Health = NewHealth;
	OnHealthChange.Broadcast(nullptr, this, NewHealth, Value);

}

float USAttributeComponent::GetMeleeAttackRange()
{
	return MeleeAttackRange;
}

bool USAttributeComponent::IsAlive()
{
	return Health > 0;
}

// Called every frame
void USAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

