// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "TankPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Distance to the player(tank)
	if (Tank)
	{
		float Distance = FVector::Distance(GetActorLocation(), Tank->GetActorLocation());

		//if the player is in range
		if (Distance <= FireRange)
		{
			//if in range rotate turret to player
			RotateTurret(Tank->GetActorLocation());
		}
	}

	if(InFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}

}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATankPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
	//if the player is in range
	if (Tank == nullptr)
	{
		return;
	}
	if (InFireRange() && Tank->bPlayerAlive)
	{
		Fire();
	}
}

bool ATower::InFireRange()
{
	//if the player is in range
	if (Tank)
	{
		float Distance = FVector::Distance(GetActorLocation(), Tank->GetActorLocation());

		if (Distance <= FireRange)
		{
			return true;
		}
	}
	return false;
}
