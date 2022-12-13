// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSJumppadActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AFPSJumppadActor::AFPSJumppadActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(200.0f));
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this,&AFPSJumppadActor::TriggerJumppad);
	RootComponent = BoxComp;



	ArrowMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMesh"));
	ArrowMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ArrowMeshComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	BoxMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	BoxMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxMeshComp->SetCollisionResponseToAllChannels(ECR_Ignore);


	ArrowMeshComp->SetupAttachment(RootComponent);
	BoxMeshComp->SetupAttachment(RootComponent);
}

void AFPSJumppadActor::TriggerJumppad(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor == nullptr) {
		return;
	}
	AFPSCharacter* myPawn = Cast<AFPSCharacter>(OtherActor);
	if (myPawn) {
		myPawn->LaunchCharacter((GetActorForwardVector() + GetActorUpVector()) * launchPower, true, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particle, GetActorLocation());
	}
	else {
		OtherComp->SetPhysicsLinearVelocity((GetActorForwardVector() + GetActorUpVector()) * launchPower);
;		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particle, GetActorLocation());
	}
}

// Called when the game starts or when spawned
void AFPSJumppadActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSJumppadActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

