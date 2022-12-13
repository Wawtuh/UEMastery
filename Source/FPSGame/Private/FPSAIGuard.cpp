// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "Math/RotationMatrix.h"
#include "FPSGameMode.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/TargetPoint.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);

	GuardState = EAIState::Idle;
}

void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn) {
	if (SeenPawn == nullptr) return;

	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);
	AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GM) {
		GM->CompleteMission(SeenPawn, false);
	}
	SetGuardState(EAIState::Alerted);
}

void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume) {
	if (GuardState == EAIState::Alerted) return;

	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);
	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;

	SetActorRotation(NewLookAt);

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);

	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation,this, &AFPSAIGuard::ResetOrienTation, 3.0f, false);

	SetGuardState(EAIState::Suspicious);
}

void AFPSAIGuard::ResetOrienTation() {
	if (GuardState == EAIState::Alerted) return;

	SetActorRotation(OriginalRotation);
	SetGuardState(EAIState::Idle);
	if (bIsPatrolling) {
		Patrol();
	}
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	bIsPatrolling = tp1 != nullptr && tp0 != nullptr;
	OriginalRotation = GetActorRotation();
	if (bIsPatrolling) {
		Patrol();
	}
}

void AFPSAIGuard::SetGuardState(EAIState NewState) {
	if (GuardState == NewState) {
		return;
	}
	GuardState = NewState;
	OnStateChanged(GuardState);
}

void AFPSAIGuard::Patrol() {
	if (destination == nullptr || destination==tp1) {
		destination = tp0;
	}
	else {
		destination = tp1;
	}
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), destination->GetActorLocation());
}
 
// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsPatrolling&&destination != nullptr) {
		if (GuardState != EAIState::Idle) {
			GetController()->StopMovement();
		}
		if (100.0f > (destination->GetActorLocation() - GetActorLocation()).Size()) {
			Patrol();
			UE_LOG(LogTemp,Warning, TEXT("Warning"));
		}
	}

}

// Called to bind functionality to input
void AFPSAIGuard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

