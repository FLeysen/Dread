// Fill out your copyright notice in the Description page of Project Settings.

#include "..\Public\DreadBombActor.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ADreadBombActor::ADreadBombActor()
	: ExplodeDelay{ 2.0f }
	, MeshComp{ CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"))}
	, ExplosionTemplate{}
	, MaterialInst{}
	, CurrentColor{}
	, TargetColor{}
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void ADreadBombActor::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle explodeTimerHandle{};
	GetWorldTimerManager().SetTimer(explodeTimerHandle, this, &ADreadBombActor::Explode, ExplodeDelay);

	MaterialInst = MeshComp->CreateAndSetMaterialInstanceDynamic(0);
	if (MaterialInst)
	{
		CurrentColor = MaterialInst->K2_GetVectorParameterValue("Color");
	}

	TargetColor = FLinearColor::MakeRandomColor();
}

void ADreadBombActor::Explode()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionTemplate, GetActorLocation());

	FCollisionObjectQueryParams QueryParams{};
	QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	QueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);

	FCollisionShape CollShape{};
	CollShape.SetSphere(500.0f);

	TArray<FOverlapResult> OutOverlaps{};
	GetWorld()->OverlapMultiByObjectType(OutOverlaps, GetActorLocation(), FQuat::Identity, QueryParams, CollShape);

	for (FOverlapResult Result : OutOverlaps)
	{
		UPrimitiveComponent* Overlap{ Result.GetComponent() };
		if (Overlap && Overlap->IsSimulatingPhysics())
		{
			UMaterialInstanceDynamic* MatInst{ Overlap->CreateAndSetMaterialInstanceDynamic(0) };
			if (MatInst)
			{
				MatInst->SetVectorParameterValue("Color", TargetColor);
			}
		}
	}

	Destroy();
}

void ADreadBombActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MaterialInst)
	{
		float Progress{ (GetWorld()->TimeSeconds - CreationTime) / ExplodeDelay };

		FLinearColor NewColor{ FLinearColor::LerpUsingHSV(CurrentColor, TargetColor, Progress) };

		MaterialInst->SetVectorParameterValue("Color", NewColor);
	}
}

