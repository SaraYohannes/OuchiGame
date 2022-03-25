// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainCharacter.generated.h"

UCLASS()
class WEEK12LECTURE_API AMainCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**mesh*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* Mesh{nullptr};
	/**cameraboom*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraBoom")
	class USpringArmComponent* CameraBoom{nullptr};
	
	/**camera*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* Camera{nullptr};

	/**movement*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementComp)
	class UPawnMovementComponent* MovementComponent{nullptr};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float Speed;

private:

	/**movement*/
	FVector CurrentVelocity;
	FVector NewLocation;
	FRotator NewRotation;
	FVector2D CameraInput;
	/**movement-direction*/
	void MoveForward(float Value);
	void MoveRight(float Value);
	
	/**camera*/
	void CameraPitch(float AxisValue);
	void CameraYaw(float AxisValue);
	
};
