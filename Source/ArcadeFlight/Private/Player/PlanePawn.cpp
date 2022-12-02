// Copyright Jonathan Justin Rampersad 2022


#include "Player/PlanePawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlanePawn::APlanePawn()
	: ThrottleValue(0.f), ThrottleChangeRate(3000.f)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	Base->SetSimulatePhysics(true);
	Base->SetAngularDamping(5.f);
	Base->SetEnableGravity(false);
	Base->SetVisibility(false);
	SetRootComponent(Base);

	PlaneBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneBase"));
	PlaneBase->SetupAttachment(GetRootComponent());

	PlanePropeller = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanePropeller"));
	PlanePropeller->SetupAttachment(GetRootComponent());

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
}

// Called when the game starts or when spawned
void APlanePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlanePawn::PitchControl(float Value)
{
	const FVector Torque = Base->GetRightVector() * (Value * 500.f);
	Base->AddTorqueInDegrees(Torque, NAME_None, true);
}

void APlanePawn::RollControl(float Value)
{
	const FVector Torque = Base->GetForwardVector() * (Value * 500.f);
	Base->AddTorqueInDegrees(Torque, NAME_None, true);
}

void APlanePawn::YawControl(float Value)
{
	const FVector Torque = Base->GetUpVector() * (Value * 500.f);
	Base->AddTorqueInDegrees(Torque, NAME_None, true);
}

void APlanePawn::Throttle(float Value)
{
	ThrottleValue = FMath::Clamp(ThrottleValue + (Value * ThrottleChangeRate * GetWorld()->GetDeltaSeconds()), 0.f, 10000.f);
}

// Called every frame
void APlanePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Base->AddForce(FVector(0.f, 0.f, -1000.f), NAME_None, true);
	
	const FVector Movement = FMath::Lerp(Base->GetPhysicsLinearVelocity(), Base->GetForwardVector() * ThrottleValue, 0.01); 
	Base->SetPhysicsLinearVelocity(Movement);
}

// Called to bind functionality to input
void APlanePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Pitch", this, &APlanePawn::PitchControl);
	PlayerInputComponent->BindAxis("Roll", this, &APlanePawn::RollControl);
	PlayerInputComponent->BindAxis("Yaw", this, &APlanePawn::YawControl);
	PlayerInputComponent->BindAxis("Throttle", this, &APlanePawn::Throttle);
}

