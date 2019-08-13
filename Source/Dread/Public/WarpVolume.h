// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerBroadcaster.h"
#include "WarpVolume.generated.h"

class UBoxComponent;
class UArrowComponent;
class UStaticMeshComponent;

UCLASS()
class DREAD_API AWarpVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWarpVolume();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	UFUNCTION()
	void OnEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, Category = Components)
	UBoxComponent* ColliderComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	UArrowComponent* ArrowComponent;

	AActor* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
	float MaxHorizontalAngleFromArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
	FVector TeleportDirection;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UStaticMeshComponent* PlaceholderMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
	TArray<AActor*> TriggerReceivers;
};
