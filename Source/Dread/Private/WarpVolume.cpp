// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/WarpVolume.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AWarpVolume::AWarpVolume()
	: ColliderComponent{ CreateDefaultSubobject<UBoxComponent>(TEXT("ColliderComponent")) }
	, ArrowComponent{ CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent")) }
	, Player{ nullptr }
	, MaxHorizontalAngleFromArrow{ 30.f }
	, TeleportDirection{}
	, PlaceholderMeshComponent{ CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent")) }
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = ColliderComponent;
	ArrowComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	ColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &AWarpVolume::OnEnter);
	ColliderComponent->OnComponentEndOverlap.AddDynamic(this, &AWarpVolume::OnExit);
	PlaceholderMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	PlaceholderMeshComponent->bIsEditorOnly = true;
	PlaceholderMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
}

// Called when the game starts or when spawned
void AWarpVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWarpVolume::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	PlaceholderMeshComponent->SetWorldTransform(FTransform{ GetActorLocation() + TeleportDirection });
}

void AWarpVolume::OnEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->GetName().Equals(FString{ TEXT("Player") }))
		return;
	Player = OtherActor;
}

void AWarpVolume::OnExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor->GetName().Equals(FString{ TEXT("Player") }))
		return;
	Player = nullptr;
}

// Called every frame
void AWarpVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Player) return;
	
	FVector playerForward{ Player->GetActorForwardVector() };
	FVector arrowForward{ ArrowComponent->GetForwardVector() };
	float angle{ float(atan2(playerForward.Y, playerForward.X) - atan2(arrowForward.Y, arrowForward.X)) * 180.f / PI };
	UE_LOG(LogTemp, Warning, TEXT("Angle is %f"), angle);
	UE_LOG(LogTemp, Warning, TEXT("Forward of player is %s"), *playerForward.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Forward of arrow is %s"), *arrowForward.ToString());

	if (angle < MaxHorizontalAngleFromArrow || angle > (360.0f - MaxHorizontalAngleFromArrow))
	{
		FVector teleportTarget{ TeleportDirection + Player->GetActorLocation() };
		Player->SetActorLocation(teleportTarget, false, nullptr, ETeleportType::TeleportPhysics);
		Player = nullptr;
	}
}

