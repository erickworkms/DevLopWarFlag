


#include "NPCObjective.h"

#include "DevLopWar/GameModes/DevLopWarGameMode.h"
#include "Net/UnrealNetwork.h"

AObjectiveNPC::AObjectiveNPC()
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

	bReplicates = true;
}

void AObjectiveNPC::GameTimer_Implementation()
{
	AGameModeBase* GameModeFound = GetWorld()->GetAuthGameMode();
	ADevLopWarGameMode* GameMode = Cast<ADevLopWarGameMode>(GameModeFound);
	IsBlocked = false;
	GameMode->EnableObjectivePoints(TerritoryIndex,IsBlocked);
}

void AObjectiveNPC::BeginPlay()
{
	Super::BeginPlay();
}

void AObjectiveNPC::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AObjectiveNPC,Portal);
}


