// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Kismet/GameplayStatics.h>
#include <AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h>
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include <DrawDebugHelpers.h>
#include <GameFramework\CharacterMovementComponent.h>
#include "SAttributeComponent.h"
#include <Components/SphereComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include "SInteractionComponent.h"
#include "SGameplayInterface.h"
#include "SActionComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
	SpringArmComp->bUsePawnControlRotation = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	AtttriComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	bIsButtonPressed = false;
	AttackRange = CreateDefaultSubobject<USphereComponent>("AttackRange");
	AttackRange->SetupAttachment(RootComponent);
	bCanAttack = true;
	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InterractionComp");
	ActionComp = CreateDefaultSubobject<USActionComponent>("ActionComp");
}

void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASCharacter::LeftClickButtonActionStart()
{
	bIsButtonPressed = true;
}

void ASCharacter::LeftClickButtonActionStop()
{
	bIsButtonPressed = false;
}

void ASCharacter::PrimaryAttack( )
{


	ActionComp->StarActionByName(this,"PrimaryAttack");
	//if (bCanAttack)
	//{
	//	GetCharacterMovement()->StopMovementImmediately();
	//	FRotator ActorRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetActor->GetActorLocation());
	//	SetActorRotation(ActorRotation);
	//	PlayAnimMontage(PrimaryAttackAnim);
	//	bCanAttack = false;
	//	GetWorldTimerManager().SetTimer(TimeForAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 1.0f);
	//	USAttributeComponent* ActorAttributeComp = Cast<USAttributeComponent>(TargetActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	//	if (ActorAttributeComp)
	//	{
	//		ActorAttributeComp->ApplyHealtChange(-20.0f);
	//	}
	//}
}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	bCanAttack = true;
}

AActor* ASCharacter::FocusActor()
{
	FHitResult HitResult;
	TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
	ObjectTypes.Add(ObjectTypeQuery3);

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursorForObjects(ObjectTypes, true, HitResult);

	return HitResult.GetActor();
}

void ASCharacter::MoveTOActor()
{
	TArray<AActor*> OutOverlappingActors;
	AttackRange->GetOverlappingActors(OutOverlappingActors);
	if (OutOverlappingActors.Contains(TargetActor))
	{	

		ActionWithActor(TargetActor);
	
	}
	else
	{
		UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), TargetActor);
	}		
	
}

void ASCharacter::MoveToClick()
{
	ETraceTypeQuery TraceChannel;
	TraceChannel = TraceTypeQuery1;
	FHitResult HitResult;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursorByChannel(TraceChannel, true, HitResult);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), HitResult.Location);
}

void ASCharacter::ActionWithActor(AActor* ActionActor)
{

	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(ActionActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	if (AttributeComp)
	{
		PrimaryAttack();
	}
	else if (ActionActor->Implements<USGameplayInterface>())
	{
		InteractWithActor(ActionActor);
	}else
	{
		UE_LOG(LogTemp, Log, TEXT("Other Action"));
	}

}

void ASCharacter::InteractWithActor(AActor* InteractActor)
{
	InteractionComp->PrimaryInteract(InteractActor);
}

void ASCharacter::MeleeAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (TargetActor)
	{
		if (TargetActor->GetActorNameOrLabel() == OtherActor->GetActorNameOrLabel())
		{	
			ActionWithActor(TargetActor);

		}
	}
}
	
AActor* ASCharacter::GetTargetActor()
{
	return TargetActor;
}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttackRange->IgnoreActorWhenMoving(GetInstigator(), true);
	AttackRange->OnComponentBeginOverlap.AddDynamic(this, &ASCharacter::MeleeAttack);


}

void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsButtonPressed)
	{
		TargetActor = FocusActor();
		if (TargetActor)
		{
			MoveTOActor();
		}
		else
		{
			MoveToClick();
		}
	}
}

void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("MoveToLocation", IE_Pressed, this, &ASCharacter::LeftClickButtonActionStart);
	PlayerInputComponent->BindAction("MoveToLocation", IE_Released, this, &ASCharacter::LeftClickButtonActionStop);
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);

}

