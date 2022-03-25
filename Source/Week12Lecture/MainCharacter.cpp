// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	//cameraboom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(Mesh);
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 3.f;
	CameraBoom->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

	//camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	//movement
	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = Mesh;
	
	Speed = 100;
	CurrentVelocity = FVector(0.f);

	//posses player 1
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//movement
	NewLocation = GetActorLocation()+(CurrentVelocity*DeltaTime);
	SetActorRelativeLocation(NewLocation);

	NewRotation = GetActorRotation();
	//yaw
	NewRotation.Yaw += CameraInput.X;
	SetActorRelativeRotation(NewRotation);
	//pitch
	FRotator NewCameraBoomRotation = CameraBoom->GetComponentRotation();
	NewCameraBoomRotation.Pitch = FMath::Clamp(NewCameraBoomRotation.Pitch += CameraInput.Y, -80.f, -15.f);
	CameraBoom->SetWorldRotation(NewCameraBoomRotation);
	
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	 InputComponent->BindAxis("Forward", this, &AMainCharacter::MoveForward);
	 InputComponent->BindAxis("Right", this, &AMainCharacter::MoveRight);
	
	 InputComponent->BindAxis("CameraPitch", this, &AMainCharacter::CameraPitch);
	 InputComponent->BindAxis("CameraYaw", this, &AMainCharacter::CameraYaw);
}

void AMainCharacter::MoveForward(float Value) 
{
	FVector Forward = GetActorForwardVector();

	if (MovementComponent)
	{
		MovementComponent->AddInputVector(Forward*Value);
	}
	
}

void AMainCharacter::MoveRight(float Value)
{
	FVector Right = GetActorRightVector();

	if (MovementComponent)
	{
		MovementComponent->AddInputVector(Right*Value);
	}
	
}

void AMainCharacter::CameraPitch(float AxisValue)
{
	CameraInput.Y = AxisValue;
	
}

void AMainCharacter::CameraYaw(float AxisValue)
{
	CameraInput.X = AxisValue;
	
}



