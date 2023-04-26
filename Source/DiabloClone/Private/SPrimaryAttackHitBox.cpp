// Fill out your copyright notice in the Description page of Project Settings.


#include "SPrimaryAttackHitBox.h"
#include <Components/BoxComponent.h>

// Sets default values
ASPrimaryAttackHitBox::ASPrimaryAttackHitBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
}

// Called when the game starts or when spawned
void ASPrimaryAttackHitBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASPrimaryAttackHitBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

