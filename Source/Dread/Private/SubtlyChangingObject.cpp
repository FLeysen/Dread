// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/SubtlyChangingObject.h"

// Sets default values
ASubtlyChangingObject::ASubtlyChangingObject()
	: RotationChange{}
	, PositionChange{}
	, DisplayMode{ ETransformTargetDisplayMode::ObjectOnly }
	, Mesh{ CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")) }
	, Visualizer{  }
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = Mesh;
	Visualizer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visualizer"));
	Visualizer->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	Visualizer->bIsEditorOnly = true;
	Visualizer->SetCollisionResponseToAllChannels(ECR_Ignore);
	Visualizer->SetStaticMesh(Mesh->GetStaticMesh());
}

// Called when the game starts or when spawned
void ASubtlyChangingObject::BeginPlay()
{
	Super::BeginPlay();
	Mesh->SetVisibility(true);
	Visualizer->SetActive(false);
}

// Called every frame
void ASubtlyChangingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASubtlyChangingObject::SimpleReceive_Implementation()
{

	return true;
}

void ASubtlyChangingObject::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName() == FName(TEXT("Mesh"))) Visualizer->SetStaticMesh(Mesh->GetStaticMesh());
	switch (DisplayMode)
	{
	case ETransformTargetDisplayMode::ObjectOnly:
		Mesh->SetVisibility(true);
		Visualizer->SetActive(false);
		Visualizer->SetVisibility(false);
		break;
	case ETransformTargetDisplayMode::PreviewTarget:
		Visualizer->SetActive(true);
		Visualizer->SetVisibility(true);
		break;
	case ETransformTargetDisplayMode::TargetOnly:
		Mesh->SetVisibility(false);
		Visualizer->SetActive(true);
		Visualizer->SetVisibility(true);
		break;
	}
	FRotator orientation{ RotationChange.X, RotationChange.Y, RotationChange.Z };
	Visualizer->SetWorldLocationAndRotationNoPhysics(GetActorLocation() + PositionChange, orientation);

}