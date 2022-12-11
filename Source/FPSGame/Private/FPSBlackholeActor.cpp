// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBlackholeActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/Spherecomponent.h"

// Sets default values
AFPSBlackholeActor::AFPSBlackholeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//검은 구 매시를 나타내는 comp 설정
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	RootComponent = MeshComp;


	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(MeshComp);

}

// Called when the game starts or when spawned
void AFPSBlackholeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSBlackholeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSBlackholeActor::DragBoxes()
{
	SphereComp->GetOverlappingComponents(dragComps);
	for (auto& otherComp : dragComps) {
		if (otherComp != NULL && otherComp->IsSimulatingPhysics()) {
			otherComp->AddRadialForce(GetActorLocation(), SphereComp->GetScaledSphereRadius(), dragForceScale, ERadialImpulseFalloff::RIF_Linear);
		}
	}
}

void AFPSBlackholeActor::DeleteBox(){
	MeshComp->GetOverlappingComponents(delComps);
	for (auto& otherComp : delComps) {
		if (otherComp != NULL && otherComp->IsSimulatingPhysics()) {
			otherComp->GetOwner()->Destroy();
		}
	}
}

