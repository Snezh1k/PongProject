#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongWall.generated.h"

class UBoxComponent;

UCLASS()
class PONGPROJECT_API APongWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APongWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UBoxComponent* BoxComponent;
};
