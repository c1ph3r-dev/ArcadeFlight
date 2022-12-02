// Copyright Jonathan Justin Rampersad 2022


#include "Environment/Ring.h"

#include "ArcadeFlightGameModeBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlanePawn.h"

void ARing::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                      int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const auto Plane = Cast<APlanePawn>(OtherActor);
	if(Plane)
	{
		const auto GameMode = Cast<AArcadeFlightGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if(GameMode)
			GameMode->AddScore();
		
		Explode(CollisionBox->GetComponentLocation());
		Destroy();
	}
}

// Sets default values
ARing::ARing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")));

	Ring = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring"));
	Ring->SetupAttachment(GetRootComponent());

	CollisionBox = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	CollisionBox->InitBoxExtent(FVector(10.f, 1025.f, 1025.f));
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Overlap);
	CollisionBox->SetupAttachment(GetRootComponent());

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ARing::OnOverlap);
}

// Called when the game starts or when spawned
void ARing::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

