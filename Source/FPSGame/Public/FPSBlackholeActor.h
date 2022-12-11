// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBlackholeActor.generated.h"

class USphereComponent;
UCLASS()
class FPSGAME_API AFPSBlackholeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSBlackholeActor();

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Compoents")
		float dragForceScale = 32.0;

	TSet<UPrimitiveComponent*> dragComps;
	TSet<UPrimitiveComponent*> delComps;

	UPROPERTY(VisibleAnywhere, Category = "Compoents")
		UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Compoents")
		USphereComponent* SphereComp;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "BlackholeAction")
	virtual void DragBoxes();

	UFUNCTION(BlueprintCallable, Category = "BlackholeAction")
	virtual void DeleteBox();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
