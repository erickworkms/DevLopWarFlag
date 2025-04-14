


#include "SpawnPoint.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
	NPCLocalReference = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraReference"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Reference(
			TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (Reference.Succeeded())
	{
		NPCLocalReference->SetStaticMesh(Reference.Object);
		NPCLocalReference->bFillCollisionUnderneathForNavmesh = false;
		NPCLocalReference->SetCanEverAffectNavigation(false);
	}

	NPCLocalReference->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	NPCLocalReference->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	NPCLocalReference->bHiddenInGame = true;

	bReplicates = true;
}
