
#include "SpawnNPC.h"
#include "EngineUtils.h"
#include "NPCObjective.h"
#include "NPC_Base.h"

// Sets default values
ASpawnNPC::ASpawnNPC()
{
	NPCLocalReference = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraReference"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Reference(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (Reference.Succeeded())
	{
		NPCLocalReference->SetStaticMesh(Reference.Object);
	}

	NPCLocalReference->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bReplicates = true;
}

void ASpawnNPC::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(Timer, this, &ASpawnNPC::CreateNPC, 5, true);
}

void ASpawnNPC::CreateNPC_Implementation()
{
	ANPC_Base* NPC = GetWorld()->SpawnActorDeferred<ANPC_Base>(
			ANPC_Base::StaticClass(),FTransform(GetActorRotation(),GetActorLocation()));
	if (NPC)
	{
		TArray<AObjectiveNPC*> NPCList;
		for (TActorIterator<AObjectiveNPC> It(GetWorld()); It; ++It)
		{
			if (It->TeamTerritory != ETeam::Clients)
			{
				NPCList.Add(*It);
			}
		}
		NPC->ObjectivePatrolLocation = NPCList[FMath::RandRange(0, NPCList.Num() - 1)];
		NPC->FinishSpawning(FTransform(GetActorRotation(),GetActorLocation()));}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow,"NPCS failed");
	}
}
