// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

ATankPlayer::ATankPlayer()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATankPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATankPlayer::MovePlayer);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATankPlayer::RotatePlayer);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATankPlayer::Fire);
}

// Called every frame
void ATankPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false,HitResult);
		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATankPlayer::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bPlayerAlive = false;
}

// Called when the game starts or when spawned
void ATankPlayer::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());

}

void ATankPlayer::MovePlayer(float value)
{
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = value * MoveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);

}

void ATankPlayer::RotatePlayer(float value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = value * RotateSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);
}
