// Copyright Jonathan Justin Rampersad 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlanePawn.generated.h"

UCLASS()
class ARCADEFLIGHT_API APlanePawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* Base;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* PlaneBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* PlanePropeller;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta=(AllowPrivateAccess="true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta=(AllowPrivateAccess="true"))
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Controls|Throttle", meta=(AllowPrivateAccess="true"))
	float ThrottleValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Controls|Throttle", meta=(AllowPrivateAccess="true"))
	float ThrottleChangeRate;
	
public:
	// Sets default values for this pawn's properties
	APlanePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PitchControl(float Value);
	void RollControl(float Value);
	void YawControl(float Value);
	void Throttle(float Value);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
