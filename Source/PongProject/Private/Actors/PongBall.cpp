


#include "Actors/PongBall.h"

#include "Actors/PongGoal.h"
#include "Actors/PongWall.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Core/PongPlayer.h"

// Sets default values
APongBall::APongBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh Component");
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComponent->SetEnableGravity(false);
	StaticMeshComponent->SetConstraintMode(EDOFMode::XYPlane);

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere Collision");
	SphereComponent->SetupAttachment(StaticMeshComponent);
	SphereComponent->SetCollisionProfileName("Trigger");
	
	bGameOver = false;
}

// Called when the game starts or when spawned
void APongBall::BeginPlay()
{
	Super::BeginPlay();

	SetReplicateMovement(true);
	if(BallMesh) {
		StaticMeshComponent->SetStaticMesh(BallMesh);
	}
	OnActorBeginOverlap.AddDynamic(this, &APongBall::OnPlatformHit);
}

void APongBall::OnPlatformHit(AActor* OverlappedActor, AActor* OtherActor)
{
	APongPlayer* PongPlayer = Cast<APongPlayer>(OtherActor);
	if(IsValid(PongPlayer)) {
		const FVector BallLinearVelocity = StaticMeshComponent->GetPhysicsLinearVelocity();
		const FVector PlatformLinearVelocity = PongPlayer->GetStaticMeshComponent()->GetPhysicsLinearVelocity();

		const FVector NewBallLinearVelocity = FVector(
			PlatformLinearVelocity.X + FMath::RandRange(-300.f, 300.f),
			BallLinearVelocity.Y * -1.f,
			BallLinearVelocity.Z);
		StaticMeshComponent->SetPhysicsLinearVelocity(NewBallLinearVelocity);
	}
	APongWall* PongWall = Cast<APongWall>(OtherActor);
	if(PongWall) {
		const FVector BallLinearVelocity = StaticMeshComponent->GetPhysicsLinearVelocity();
		const FVector NewBallLinearVelocity = FVector(
			BallLinearVelocity.X * -1.f,
			BallLinearVelocity.Y,
			BallLinearVelocity.Z);
		StaticMeshComponent->SetPhysicsLinearVelocity(NewBallLinearVelocity);
	}

	APongGoal* PongGoal = Cast<APongGoal>(OtherActor);
	if(PongGoal) {
		Restart();
	}
}

// Called every frame
void APongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APongBall::Start()
{
	bGameOver = false;
	SetActorLocation(FVector::ZeroVector);
	StaticMeshComponent->SetPhysicsLinearVelocity(FVector(
		FMath::RandRange(-300.f, 300.f),
		(FMath::RandBool() ? 1.f : -1.f) * 500.f,
		0.f));
}

void APongBall::Restart()
{
	SetActorLocation(FVector::ZeroVector);
	StaticMeshComponent->SetPhysicsLinearVelocity(FVector(
		FMath::RandRange(-300.f, 300.f),
		(FMath::RandBool() ? 1.f : -1.f) * 500.f,
		0.f));
}

void APongBall::GameOver()
{
	bGameOver = true;
	StaticMeshComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);
}

