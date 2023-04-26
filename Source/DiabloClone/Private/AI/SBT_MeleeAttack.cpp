// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBT_MeleeAttack.h"
#include <AIModule/Classes/AIController.h>
#include <AIModule/Classes/BehaviorTree/BlackboardComponent.h>
#include <Animation/AnimMontage.h>
#include <GameFramework/Character.h>



EBTNodeResult::Type USBT_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();
	if (ensure(MyController))
	{
		ACharacter* MyPawn = Cast<ACharacter>(MyController->GetPawn());
		if (MyPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}


		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActorKey.SelectedKeyName));

		if (TargetActor == nullptr)
		{
			return EBTNodeResult::Failed;

		}

		MyPawn->PlayAnimMontage(AttackAnim);

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}