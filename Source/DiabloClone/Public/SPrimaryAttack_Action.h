// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SPrimaryAttack_Action.generated.h"

/**
 * 
 */
class UAnimMontage;
class ASCharacter;
UCLASS()
class DIABLOCLONE_API USPrimaryAttack_Action : public USAction
{
	GENERATED_BODY()
public:
	USPrimaryAttack_Action();
protected:
	UPROPERTY(EditDefaultsOnly,Category="Animation")
	UAnimMontage* AttackAnimClass;
	UPROPERTY(EditDefaultsOnly,Category="Timer")
	float AnimDelay;
	UPROPERTY(EditDefaultsOnly,Category="Attack")
	float AttackDamage;
	UFUNCTION()
	void Action_TimeElapsed(ASCharacter* Instigator);
public:
	
	virtual void StartAction_Implementation(AActor* InstigatorActor) override;
};
