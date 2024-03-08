#include "Core/PongPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APongPlayer::APongPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh Component");
	StaticMeshComponent->SetCollisionProfileName(FName("PhysicsActor"));
	RootComponent = StaticMeshComponent;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	BoxComponent->SetupAttachment(GetRootComponent());
	BoxComponent->SetCollisionProfileName(FName("PhysicsActor"));

	ArmComponent = CreateDefaultSubobject<USpringArmComponent>("Arm Component");
	ArmComponent->SetupAttachment(RootComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComponent->SetupAttachment(ArmComponent);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("Floating Pawn Movement");
	//SetReplicateMovement(true);
	FloatingPawnMovement->SetIsReplicated(true);
}

// Called when the game starts or when spawned
void APongPlayer::BeginPlay()
{
	Super::BeginPlay();

	SetReplicateMovement(true);
}

// Called every frame
void APongPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GetActorLocation().X < -420.f || GetActorLocation().X > 420.f){
		SetActorLocation(FVector(FMath::Clamp(GetActorLocation().X, -421.f, 421.f), GetActorLocation().Y, GetActorLocation().Z));
	}
}

// Called to bind functionality to input
void APongPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APongPlayer::MovePlatform(float Value)
{
	/*if(Value != 0.f) {
		AddMovementInput(FVector(1.f, 0.f, 0.f), Value, true);
		/*FVector DeltaLocation = FVector::ZeroVector;
		DeltaLocation.Y = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed;
		AddActorLocalOffset(DeltaLocation, true);#1#
	}*/
	ServerMovePlatform(Value);
}

void APongPlayer::ServerMovePlatform_Implementation(float Value)
{
	BroadcastMovePlatform(Value);
	//if (Role == ROLE_Authority) {}
}

bool APongPlayer::ServerMovePlatform_Validate(float Value)
{
	return true;
}

void APongPlayer::BroadcastMovePlatform_Implementation(float Value)
{
	AddActorLocalOffset(FVector(0, 10 * Value, 0));
}

