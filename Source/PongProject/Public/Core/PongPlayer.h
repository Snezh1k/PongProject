

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "PongPlayer.generated.h"

class UBoxComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PONGPROJECT_API APongPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APongPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="Movement")
	void MovePlatform(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerMovePlatform(float Value);
	void ServerMovePlatform_Implementation(float Value);
	bool ServerMovePlatform_Validate(float Value);
	
	UFUNCTION(NetMulticast, Reliable)
	void BroadcastMovePlatform(float Value);
	void BroadcastMovePlatform_Implementation(float Value);

	UStaticMeshComponent* GetStaticMeshComponent() const { return StaticMeshComponent; };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Config")
	float Speed = 500.f;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	UFloatingPawnMovement* FloatingPawnMovement;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USpringArmComponent* ArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UCameraComponent* CameraComponent;
};
