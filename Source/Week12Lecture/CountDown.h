// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "CountDown.generated.h"

UCLASS()
class WEEK12LECTURE_API ACountDown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountDown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int32 CountDownTime; //int32 is a type just as int is

	FTimerHandle CountDownTimerHandle; //struct of Timer Handle

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CountDown")
	TArray<UStaticMeshComponent*> Light{nullptr}; //UstaticMeshComponent is the pointer, not the TArray

	/**countdown visualized as text in the middle of the screen*/
	UTextRenderComponent* CountDownText{nullptr};

	void DisplayCountDownTimer();	//display timer
	void UpdateCountDownTimer();	//update timer
	void FinishedCountDownTimer();	//has timer finished?
};