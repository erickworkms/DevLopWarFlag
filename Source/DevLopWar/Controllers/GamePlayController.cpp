
#include "GamePlayController.h"
#include "Net/UnrealNetwork.h"
#include "EngineUtils.h"
#include "DevLopWar/Structs/Struct.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/Characters/NPC/SpawnPoint.h"
#include "DevLopWar/Characters/Player/Player_Base.h"
#include "DevLopWar/PlayerStates/DevOpPlayerState.h"


void AGamePlayController::RevivePlayer_Implementation()
{
	UWorld* World = GetWorld();
	check(World);
	
	APlayer_Base* BasePlayer = Cast<APlayer_Base>(GetPawn());
	if (IsValid(BasePlayer))
	{
		BasePlayer->Life = 100;
		BasePlayer->Action = NoCharacterData;
	
		if (GetLocalRole() == ROLE_Authority)
		{
			TArray<ASpawnPoint*> Objetivo;
			for (TActorIterator<ASpawnPoint> It(World); It; ++It)
			{
				Objetivo.Add(*It);
			}
			if (Objetivo.Num() > 0)
			{
				ASpawnPoint* ChosenObjective = Objetivo[FMath::RandRange(0, Objetivo.Num() - 1)];
				FVector Local = ChosenObjective->GetActorLocation();
				// Player->TeleportTo(FVector(Local.X,Local.Y,Local.Z + 50),ChosenObjective->GetActorRotation(),false,true);
				BasePlayer->SetActorLocationAndRotation(FVector(Local.X,Local.Y,Local.Z + 50),ChosenObjective->GetActorRotation(), false, nullptr, ETeleportType::TeleportPhysics);
			}
		}
	}
}

void AGamePlayController::ActiveEndGameHud_Implementation()
{
	if (IsValid(Hud))
	{
		Hud->EnableWinnerScreen();
		bShowMouseCursor = true;
		DefaultMouseCursor = EMouseCursor::Crosshairs;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow,"failed");
	}
}

void AGamePlayController::BeginPlay()
{
	Super::BeginPlay();
	SetReplicates(true);
}

void AGamePlayController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGamePlayController, BaseCharacter);
	DOREPLIFETIME(AGamePlayController, Hud);
}

void AGamePlayController::CheckInstanceData_Implementation(FPlayerGameplayInformation GameplayInformation)
{
	ADevOpPlayerState* PlayerStateData = Cast<ADevOpPlayerState>(PlayerState);
	if (IsValid(PlayerState))
	{
		PlayerStateData->SetChosenTeam(GameplayInformation.ChosenTeam);
	}
}
