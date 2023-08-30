// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "TankPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankPlayer : public ABasePawn
{
	GENERATED_BODY()

public:
	ATankPlayer();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetPlayerController() const { return TankPlayerController; }

	bool bPlayerAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotateSpeed = 100.f;

	void MovePlayer(float value);
	void RotatePlayer(float value);
	
	APlayerController* TankPlayerController;
};
