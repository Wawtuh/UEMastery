// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSJumppadActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UParticleSystem;
UCLASS()
class FPSGAME_API AFPSJumppadActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSJumppadActor();

protected:
	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnyWhere, Category = "Components")
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnyWhere, Category = "Components")
	UStaticMeshComponent* ArrowMeshComp;

	UPROPERTY(VisibleAnyWhere, Category = "Components")
	UStaticMeshComponent* BoxMeshComp;
	virtual void BeginPlay() override;

	UFUNCTION()
		void TriggerJumppad(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(BlueprintReadWrite, Category = "Variable")
		float launchPower = 1000.0f;

	UPROPERTY(EditAnyWhere, Category = "Particle")
		UParticleSystem* particle;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
