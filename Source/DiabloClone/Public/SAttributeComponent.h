// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChange, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIABLOCLONE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	USAttributeComponent();

protected:

	UPROPERTY(EditAnywhere, Category = "Attribute")
		float Health;
	UPROPERTY(EditAnywhere, Category = "Attribute")
		float HealthMax;
	UPROPERTY(EditAnywhere, Category = "Attribute")
		float Mana;
	UPROPERTY(EditAnywhere, Category = "Attribute")
		float ManaMax;
	UPROPERTY(EditAnywhere, Category = "Attack")
		float MeleeAttackRange;

	virtual void BeginPlay() override;

public:	
	
	UPROPERTY(BlueprintAssignable)
		FOnHealthChange OnHealthChange;
	UFUNCTION(BlueprintCallable, Category = "Attribute")
		float GetHealth();
	UFUNCTION(BlueprintCallable, Category = "Attribute")
		float GetHealthMax();
	UFUNCTION(BlueprintCallable, Category = "Attribute")
		float GetMana();
	UFUNCTION(BlueprintCallable, Category = "Attribute")
		float GetManaMax();
	UFUNCTION()
		void ApplyHealtChange(float Value);
	UFUNCTION(BlueprintCallable, Category = "Attribute")
		float GetMeleeAttackRange();
	UFUNCTION(BlueprintCallable,Category="Attribute")
		bool IsAlive();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
