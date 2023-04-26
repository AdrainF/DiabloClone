// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckAttackRange.h"
#include <AIModule/Classes/BehaviorTree/BlackboardComponent.h>
#include <AIModule/Classes/AIController.h>

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackBoardComp))
	{
		AActor* TargetActor = Cast<AActor>(BlackBoardComp->GetValueAsObject("TargetActor"));

		if (TargetActor)
		{
			AAIController* MyController = OwnerComp.GetAIOwner();
			if (ensure(MyController))
			{
				APawn* IAPawn = MyController->GetPawn();
				if (ensure(IAPawn))
				{
					float Distance = FVector::Distance(TargetActor->GetActorLocation(), IAPawn->GetActorLocation());

					bool bWithingRange = Distance < 150.f;

					BlackBoardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, bWithingRange);
				}
			}
		}
	}

}
