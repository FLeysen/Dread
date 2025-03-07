// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DreadBombActor.generated.h"

class UStaticMeshComponent;
class UParticleSystem;
class UMaterialInstanceDynamic;

UCLASS()
class DREAD_API ADreadBombActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADreadBombActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = BombActor)
	float ExplodeDelay;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = BombActor)
	UParticleSystem* ExplosionTemplate;

	UMaterialInstanceDynamic* MaterialInst;

	FLinearColor CurrentColor;
	FLinearColor TargetColor;

	UFUNCTION()
	void Explode();

public:
	void Tick(float DeltaTime) override;
};
