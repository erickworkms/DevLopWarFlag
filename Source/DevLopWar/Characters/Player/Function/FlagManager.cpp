
#include "FlagManager.h"

#include "DevLopWar/GameModes/DevLopWarGameMode.h"

AFlagManager::AFlagManager()
{
	NPCLocalReference = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Reference"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Reference(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (Reference.Succeeded())
	{
		NPCLocalReference->SetStaticMesh(Reference.Object);
	}

	NPCLocalReference->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	NPCLocalReference->SetCanEverAffectNavigation(false);
	NPCLocalReference->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	SetRootComponent(NPCLocalReference);
	
	bReplicates = true;
}

void AFlagManager::SetFlagLocation_Implementation(FVector NewLocation)
{
	FlagObject->SetActorLocation(NewLocation);
}

void AFlagManager::RespawnFlag_Implementation()
{
	FlagObject->SetActorLocation(StartLocation);
}

void AFlagManager::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(FlagObject))
	{
		StartLocation = FlagObject->GetActorLocation();
	}
	SetReplicateMovement(true);
}

void AFlagManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}


