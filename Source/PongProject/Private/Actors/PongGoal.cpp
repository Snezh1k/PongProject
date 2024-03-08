#include "Actors/PongGoal.h"

#include "Actors/PongBall.h"
#include "Components/BoxComponent.h"
#include "Core/PongGameState.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APongGoal::APongGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh Component");
	StaticMeshComponent->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	BoxComponent->SetupAttachment(StaticMeshComponent);
	BoxComponent->SetCollisionProfileName(FName("PhysicsActor"));
}

void APongGoal::Score(AActor* OverlappedActor, AActor* OtherActor)
{
	APongBall* PongBall = Cast<APongBall>(OtherActor);
	if(PongBall) {
		AGameStateBase* GameState = UGameplayStatics::GetGameState(this);
		if(GameState) {
			APongGameState* PongGameState = Cast<APongGameState>(GameState);
			if(PongGameState) {
				PongGameState->IncrementScore(PlayerNumber);
			}
		}
	}
}

// Called when the game starts or when spawned
void APongGoal::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &APongGoal::Score);
}

