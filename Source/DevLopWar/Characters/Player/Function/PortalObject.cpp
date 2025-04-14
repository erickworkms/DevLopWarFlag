#include "PortalObject.h"
#include "DevLopWar/Characters/Player/Player_Base.h"
#include "DevLopWar/GameModes/DevLopWarGameMode.h"
#include "DevLopWar/PlayerStates/DevOpPlayerState.h"
#include "Net/UnrealNetwork.h"

APortalObject::APortalObject()
{
	NPCLocalReference = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Reference"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Reference(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
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
	Collision->OnComponentBeginOverlap.AddDynamic(this, &APortalObject::StartCollision);
    Collision->SetIsReplicated(true);

	SetRootComponent(NPCLocalReference);

	Collision->SetupAttachment(NPCLocalReference);
	bReplicates = true;
}


void APortalObject::ShowPortal_Implementation()
{
	AGameModeBase* GameModeFound = GetWorld()->GetAuthGameMode();
	ADevLopWarGameMode* GameMode = Cast<ADevLopWarGameMode>(GameModeFound);
	if (IsValid(GameMode))
	{
		NPCLocalReference->SetVisibility(true);
		SetPortalMaterial(GameMode->GetFlagTeamOwner());
	}
	
}

void APortalObject::HidePortal_Implementation()
{
	NPCLocalReference->SetVisibility(false);
}

void APortalObject::BeginPlay()
{
	Super::BeginPlay();
	HidePortal();
	SetReplicateMovement(true);
}

void APortalObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APortalObject, NPCLocalReference);
	DOREPLIFETIME(APortalObject, Collision);
}

void APortalObject::StartCollision(UPrimitiveComponent* OverlappedComp, AActor* DetectedCharacter,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult)
{
	APlayer_Base* Character = Cast<APlayer_Base>(DetectedCharacter);
		
	if (IsValid(Character) && Character->HasFlag)
	{
		HidePortal();
		ADevOpPlayerState* PlayerStateFound = Cast<ADevOpPlayerState>(Character->GetPlayerState());
		SetPortalMaterial(PlayerStateFound->GetChosenTeam());

		FlagManager->RespawnFlag();
		Character->HasFlag = false;
		Character->DisableFlag();
		AGameModeBase* GameModeFound = GetWorld()->GetAuthGameMode();
		ADevLopWarGameMode* GameMode = Cast<ADevLopWarGameMode>(GameModeFound);
		if (IsValid(GameMode))
		{
			GameMode->ChangeTeamPoints(PlayerStateFound->GetChosenTeam());
			GameMode->ChangeTeamFlagOwner(ETeam::NoJob);
		}
	}
}
