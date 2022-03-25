// Fill out your copyright notice in the Description page of Project Settings.


#include "CountDown.h"
#include "Components/TextRenderComponent.h"

// Sets default values
ACountDown::ACountDown()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set countdown from
	CountDownTime = 3;
	
	//Countdowntext
	CountDownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountDownText"));
	SetRootComponent(CountDownText);
	CountDownText->SetHorizontalAlignment(EHTA_Center);
	CountDownText->SetWorldSize(250.0);
	CountDownText->SetTextRenderColor(FColor::Red);
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshCom(TEXT("StaticMesh'/Game/3DModels/Sphere2.Sphere2'"));

	//TArray
	//size
	Light.Init(NULL, 3);
	//build
	Light[0] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RedLight"));
	Light[1] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("YellowLight"));
	Light[2] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GreenLight"));

	// int ArraySize = Light.Num(); //local variable, keep a hold of how large the array is for looping purposes
 //    if (SphereMeshCom.Succeeded())
 //    {
	//     for(int u = 0; u < ArraySize; u++)
	//     {
	// 	    Light[u]->SetStaticMesh(SphereMeshCom.Object);
	//     }
 //    }
	
}

// Called when the game starts or when spawned
void ACountDown::BeginPlay()
{
	Super::BeginPlay();
	Light[0]->SetWorldLocation(FVector(760.f, -200.f, 350.f));
	Light[1]->SetWorldLocation(FVector(760.f, 0.f, 350.f));
	Light[2]->SetWorldLocation(FVector(760.f, 200.f, 350.f));

	DisplayCountDownTimer();
	
	GetWorld()->GetTimerManager().SetTimer(CountDownTimerHandle, this, &ACountDown::UpdateCountDownTimer, 1.0f, true);
			
}

// Called every frame
void ACountDown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACountDown::DisplayCountDownTimer()
{
	CountDownText->SetText(FText::AsNumber(CountDownTime));
}

void ACountDown::UpdateCountDownTimer()
{
	DisplayCountDownTimer();
	if (CountDownTime < 1)
	{
		FinishedCountDownTimer();
        
	}
	if (CountDownTime < 0)
	{
		//We're done counting down, so stop running the timer.
		GetWorld()->GetTimerManager().ClearTimer(CountDownTimerHandle);
		Destroy();
     
	}
	CountDownTime--;
	if (CountDownTime >= 0 && CountDownTime <3) {
		Light[CountDownTime]->DestroyComponent();
	}
}

void ACountDown::FinishedCountDownTimer()
{
	//AMainPlayer* PlayerChar = Cast<AMainPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	//PlayerChar->bGameCanPlay = true;
	CountDownText->SetTextRenderColor(FColor::Green);
	CountDownText->SetText(INVTEXT("GO!"));
}



