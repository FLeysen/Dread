// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReactsToTrigger.h"
#include "Components/StaticMeshComponent.h"
#include "SubtlyChangingObject.generated.h"

UENUM(BlueprintType)
enum class ETransformTargetDisplayMode : uint8
{
	ObjectOnly     UMETA(DisplayName = "ObjectOnly"),
	PreviewTarget  UMETA(DisplayName = "PreviewTarget"),
	TargetOnly	   UMETA(DisplayName = "TargetOnly"),
};

UCLASS()
class DREAD_API ASubtlyChangingObject : public AActor, public IReactsToTrigger
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASubtlyChangingObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Target)
		FVector RotationChange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Target)
		FVector PositionChange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Target)
		ETransformTargetDisplayMode DisplayMode;

	UPROPERTY(VisibleAnywhere, Category = Components)
		UStaticMeshComponent* Mesh;

		UStaticMeshComponent* Visualizer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = TriggerResponses)
		bool SimpleReceive();
		virtual bool SimpleReceive_Implementation() override;
};
