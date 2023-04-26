// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USAttributeComponent;
class USphereComponent;
class UAnimMontage;
class USInteractionComponent;
class USActionComponent;

UCLASS()
class DIABLOCLONE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ASCharacter();

protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> PrimaryAttackHitBoxClass;
	UPROPERTY(EditAnywhere, Category = "Camera")
		UCameraComponent* CameraComp;
	UPROPERTY(EditAnywhere, Category = "Camera")
		USpringArmComponent* SpringArmComp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
		USAttributeComponent* AtttriComp;
	UPROPERTY(EditAnywhere,Category="Attack")
		USphereComponent* AttackRange;
	UPROPERTY(EditAnywhere,Category="Animation")
		UAnimMontage* PrimaryAttackAnim;
	UPROPERTY(EditAnywhere,Category="Component")
		USInteractionComponent* InteractionComp;
	UPROPERTY(EditAnywhere,Category="Component")
		USActionComponent* ActionComp;

	FTimerHandle TimeForAttack;
	bool bCanAttack;
	bool bIsButtonPressed;
	UPROPERTY();
	AActor* TargetActor;
	void LeftClickButtonActionStart();
	void LeftClickButtonActionStop();
	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	UFUNCTION()
	AActor* FocusActor();
	void MoveTOActor();
	void MoveToClick();
	void ActionWithActor(AActor* ActionActor);
	void InteractWithActor(AActor* InteractActor);
	UFUNCTION()
	void MeleeAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;

public:
	AActor* GetTargetActor();
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
