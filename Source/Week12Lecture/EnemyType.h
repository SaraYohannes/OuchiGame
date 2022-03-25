// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyType.generated.h"

UCLASS()
class WEEK12LECTURE_API AEnemyType : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyType();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**set mesh*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
    class UStaticMeshComponent* EnemyMesh{nullptr};

	/**Sphere component to support OnOVerlap function*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpehereOverlap")
    class USphereComponent* SphereOverlap{nullptr};
	
	/**ouchi message visualized as text above actor*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ouchi-text")
	class UTextRenderComponent* Ouchi{nullptr};
	
	/**overlap function, when overlapped, send for an ouchi message*/
	UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/**display ouchi message, after message is displayed destroy actor*/
	UFUNCTION()
	void OuchiMessage();

	/**time control*/
	int32 LengthOfTimer;
	FTimerHandle CountDownOuch;

	UFUNCTION()
	void DestroyOuchi();
		
	/**when ouchi message is sent, cast for to save class to add a point one point to enemies ammount*/
	//UFUNCTION()
	//void SaveProgress();
	

	/**set texture*/
	
};
