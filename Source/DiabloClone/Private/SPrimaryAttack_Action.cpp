// Fill out your copyright notice in the Description page of Project Settings.


#include "SPrimaryAttack_Action.h"
#include <GameFramework/Actor.h>
#include "SCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <TimerManager.h>
#include "SAttributeComponent.h"

USPrimaryAttack_Action::USPrimaryAttack_Action()
{
	AnimDelay = 1.0f;
	AttackDamage = -20.0f;
}

void USPrimaryAttack_Action::Action_TimeElapsed(ASCharacter* Instigator)
{
	if (Instigator)
	{
		AActor* TargetActor=Instigator->GetTargetActor();
		if (TargetActor)
		{
			USAttributeComponent* AttriComp =Cast<USAttributeComponent>(TargetActor->GetComponentByClass(USAttributeComponent::StaticClass()));
			if (AttriComp)
			{
				AttriComp->ApplyHealtChange(AttackDamage);
			}
		}
	}
//	Instigator->GetCharacterMovement()->SetMovementMode(Move_);
}

void USPrimaryAttack_Action::StartAction_Implementation(AActor* InstigatorActor)
{
	
	
	ASCharacter* InstigatorCharacter = Cast<ASCharacter>(InstigatorActor);
	
	if (InstigatorCharacter)
	{
		InstigatorCharacter->GetCharacterMovement()->StopMovementImmediately();
	//	InstigatorCharacter->GetCharacterMovement()->DisableMovement();
		InstigatorCharacter->PlayAnimMontage(AttackAnimClass);

		FTimerHandle ActionTimer;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "Action_TimeElapsed", InstigatorCharacter);

		GetWorld()->GetTimerManager().SetTimer(ActionTimer, Delegate, AnimDelay, false);

	}
}

