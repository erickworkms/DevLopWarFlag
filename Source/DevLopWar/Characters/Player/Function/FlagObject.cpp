


#include "FlagObject.h"

#include "DevLopWar/GameModes/DevLopWarGameMode.h"
#include "Net/UnrealNetwork.h"

AFlagObject::AFlagObject()
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

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->bFillCollisionUnderneathForNavmesh = false;
	Collision->bHiddenInGame = false;
	Collision->SetVisibility(true);
	Collision->SetCanEverAffectNavigation(false);
	Collision->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f));
	Collision->SetRelativeRotation(FRotator(0, 0, 0));
	Collision->SetWorldScale3D(FVector(2, 2, 2));
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AFlagObject::StartCollision);
    Collision->SetIsReplicated(true);

	SetRootComponent(NPCLocalReference);

	Collision->SetupAttachment(NPCLocalReference);
	bReplicates = true;
}

void AFlagObject::ChangeFlagTeamOwner_Implementation(ETeam Team)
{
	AGameModeBase* GameModeFound = GetWorld()->GetAuthGameMode();
	ADevLopWarGameMode* GameMode = Cast<ADevLopWarGameMode>(GameModeFound);
	if (IsValid(GameMode))
	{
		GameMode->ChangeTeamFlagOwner(Team);
		SetActorLocation(FVector(0,0,0));
	}
}

void AFlagObject::BeginPlay()
{
	Super::BeginPlay();
	SetReplicateMovement(true);
}

void AFlagObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}


