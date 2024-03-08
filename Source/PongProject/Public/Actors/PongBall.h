

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongBall.generated.h"

class USphereComponent;

UCLASS()
class PONGPROJECT_API APongBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APongBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPlatformHit(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Config")
	UStaticMesh* BallMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Config")
	uint8 bGameOver : 1;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Start();
	void Restart();
	void GameOver();
};
