// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SBT_MeleeAttack.generated.h"

/**
 * 
 */
class UAnimMontage;
UCLASS()
class DIABLOCLONE_API USBT_MeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	virtual	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere,Category="AI")
	FBlackboardKeySelector TargetActorKey;
	UPROPERTY(EditAnywhere,Category="Attack")
	UAnimMontage* AttackAnim;
	
};
