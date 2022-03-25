// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyType.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"


// Sets default values
AEnemyType::AEnemyType()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Mesh
	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	SetRootComponent(EnemyMesh);	

	//SphereComponent
	SphereOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("SphereOverlap"));
	SphereOverlap->SetupAttachment(EnemyMesh);
	SphereOverlap->SetSphereRadius(40.0f);
	SphereOverlap->OnComponentBeginOverlap.AddDynamic(this, &AEnemyType::OnOverlap);

	//text ouch
	Ouchi = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Ouchi"));
	Ouchi->SetupAttachment(EnemyMesh);
	Ouchi->SetWorldSize(100.0);

	//time control
	LengthOfTimer = 1;
	
}

// Called when the game starts or when spawned
void AEnemyType::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyType::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyType::OuchiMessage()
{

	Ouchi->SetTextRenderColor(FColor::Red);
	Ouchi->SetText(TEXT("Ouchi!"));
	
	GetWorld()->GetTimerManager().SetTimer(CountDownOuch, this, &AEnemyType::DestroyOuchi, 1.0f, true);

}

void AEnemyType::DestroyOuchi ()
{
	if (LengthOfTimer <= 0)
	{
			this->Destroy();
	}

	LengthOfTimer--;

}

void AEnemyType::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	OuchiMessage();
	
}
