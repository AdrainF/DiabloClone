// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPrimaryAttackHitBox.generated.h"
class UBoxComponent;
UCLASS()
class DIABLOCLONE_API ASPrimaryAttackHitBox : public AActor
{
	GENERATED_BODY()
	
public:	

	ASPrimaryAttackHitBox();

protected:
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComp;

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
