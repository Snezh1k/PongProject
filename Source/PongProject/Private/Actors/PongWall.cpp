#include "Actors/PongWall.h"

#include "Components/BoxComponent.h"

APongWall::APongWall()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh Component");
	StaticMeshComponent->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	BoxComponent->SetupAttachment(StaticMeshComponent);
	BoxComponent->SetCollisionProfileName(FName("PhysicsActor"));
}

void APongWall::BeginPlay()
{
	Super::BeginPlay();
}

