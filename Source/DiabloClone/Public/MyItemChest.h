// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "MyItemChest.generated.h"

UCLASS()
class DIABLOCLONE_API AMyItemChest : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyItemChest();

protected:
	UPROPERTY(EditAnywhere,Category="Mesh")
		UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMeshComponent* LidMesh;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

};
