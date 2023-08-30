// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnActor.h"

// Sets default values
ASpawnActor::ASpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawnBoxVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	RootComponent = SpawnBoxVolume;

}

// Called when the game starts or when spawned
void ASpawnActor::BeginPlay()
{
	Super::BeginPlay();

	if (bShouldSpawn)
	{
		ScheduleActorSpawn();
	}
	
}

void ASpawnActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	//GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
}


bool ASpawnActor::SpawnActor()
{
	bool bSpawnedActor = false;

	if (ActorToSpawn)
	{
		FBoxSphereBounds BoxBounds = SpawnBoxVolume->CalcBounds(GetActorTransform());

		FVector SpawnPointLocation = BoxBounds.Origin;
		SpawnPointLocation.X += -BoxBounds.BoxExtent.X + 2 * BoxBounds.BoxExtent.X * FMath::FRand();
		SpawnPointLocation.Y += -BoxBounds.BoxExtent.Y + 2 * BoxBounds.BoxExtent.Y * FMath::FRand();
		SpawnPointLocation.Z += -BoxBounds.BoxExtent.Z + 2 * BoxBounds.BoxExtent.Z * FMath::FRand();

		FRotator SpawnPointRotation = GetActorRotation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnPointLocation, SpawnPointRotation, SpawnParams);

		if (SpawnedActor)
		{
			bSpawnedActor = true;
			SpawnCount++;
		}
	}

	return bSpawnedActor;
}

void ASpawnActor::ScheduleActorSpawn()
{
	float DeltaToNextSpawn = AvgSpawnTime + (-RandomSpawnTime + 1 * RandomSpawnTime * FMath::FRand());

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawnActor::SpawnActorScheduled, DeltaToNextSpawn, false);
}

void ASpawnActor::SpawnActorScheduled()
{
	if(SpawnActor())
	{
		if (bShouldSpawn)
		{
			ScheduleActorSpawn();
		}
	}
}

