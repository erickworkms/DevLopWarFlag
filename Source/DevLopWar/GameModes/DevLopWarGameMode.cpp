

#include "DevLopWarGameMode.h"
#include "DevLopWar/Controllers/GamePlayController.h"
#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "DevLopWar/PlayerStates/DevLopWarGameStateBase.h"
#include "DevLopWar/PlayerStates/DevOpPlayerState.h"
#include "GameFramework/HUD.h"
#include "EngineUtils.h"
#include "DevLopWar/Characters/NPC/NPC_Base.h"
#include "DevLopWar/Characters/Player/Function/FlagObject.h"
#include "UObject/ConstructorHelpers.h"

ADevLopWarGameMode::ADevLopWarGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Class'/Script/DevLopWar.Player_Base'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = NULL;
	}
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDClass(TEXT("/Game/Maps/HudGameplay"));
	if (PlayerHUDClass.Succeeded())
	{
		HUDClass = PlayerHUDClass.Class;
	}
	PlayerStateClass = ADevOpPlayerState::StaticClass();
	PlayerControllerClass = AGamePlayController::StaticClass();
	GameStateClass = ADevLopWarGameStateBase::StaticClass();

	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	bUseSeamlessTravel = true;
}

int ADevLopWarGameMode::ReturnPlayerIndex(AGamePlayController* Controller)
{
	for (int i = 0; i < PlayerRoom.Num(); i++)
	{
		if (IsValid(PlayerRoom[i]))
		{
			if (PlayerRoom[i] == Controller)
			{
				return i;
			}
		}
	}
	return 100;
}

void ADevLopWarGameMode::BeginPlay()
{
	Super::BeginPlay();
	GameStateServer = Cast<ADevLopWarGameStateBase>(GameState);
	GameInstance = Cast<UDevLopWarGameInstance>(GetWorld()->GetGameInstance());

	if (HasAuthority())
	{
		CreateRoomData = GameInstance->CreateRoomData;
		Players = GameInstance->Players;
		PlayerRoom.SetNum(GameInstance->TotalPlayersNumber);
		GameplayInformation.SetNum(GameInstance->TotalPlayersNumber);
		PlayerRoomName = GameInstance->PlayerRoomName;
		ReviverTimer.SetNum(GameInstance->TotalPlayersNumber);
		GetWorldTimerManager().SetTimer(Timer, this, &ADevLopWarGameMode::GameTimer, 0.1, true);
	}
	DetectObjectivePoints();
}

void ADevLopWarGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	if (GetLocalRole() == ROLE_Authority)
	{
		for (int i=0;i < PlayerRoom.Num();i++)
		{
			if (IsValid(PlayerRoom[i]) && PlayerRoom[i] == Exiting)
			{
				PlayerRoomName.RemoveAt(i);
				PlayerRoom.RemoveAt(i);
				Players.RemoveAt(i);
			}
		}
	}
}

void ADevLopWarGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}


void ADevLopWarGameMode::GameTimer_Implementation()
{
	if (!GameEnd)
	{
		if (GameplayTime > 0.00001 && AgileTeam < 3 && CascadeTeam < 3)
		{
			GameplayTime -= 0.1;
			GameStateServer->SetGameplayTime(GameplayTime);
			GameStateServer->SetAgilePoints(AgileTeam);
			GameStateServer->SetCascadePoints(CascadeTeam);
			GameStateServer->SetTeamFlagOwner(TeamFlagOwner);
		}
		else
		{
			GameEnd = true;
			GameplayTime = 0;
			GameStateServer->SetGameplayTime(GameplayTime);
			if (CascadeTeam > AgileTeam)
			{
				GameStateServer->SetWinnerTeam( ETeam::Cascade);
			}
			else if (AgileTeam > CascadeTeam)
			{
				GameStateServer->SetWinnerTeam( ETeam::Agile);
			}
			else
			{
				GameStateServer->SetWinnerTeam( ETeam::NoJob);
			}
			
			
			for (int i = 0; i < PlayerRoom.Num(); i++)
			{
				AGamePlayController* Controller = Cast<AGamePlayController>(PlayerRoom[i]);
				if (IsValid(Controller))
				{
					Controller->ActiveEndGameHud();
					Controller->GetPawn()->Destroy();
				}
			}
			for (TActorIterator<ANPC_Base> It(GetWorld()); It; ++It)
			{
				ANPC_Base* NPC = *It;
		
				NPC->Destroy();
			}
			GetWorldTimerManager().ClearTimer(Timer);
		}
	}
}


void ADevLopWarGameMode::UpdateTerritoryNPCDamage_Implementation(AObjectiveNPC* Territory_Detected)
{
	if (Territory_Detected->Life > 0 && Territory_Detected->IsBlocked == false && !GameStateServer->GetCheckTakenTerritory(Territory_Detected->TerritoryIndex,ETeam::Clients))
	{
		Territory_Detected->Life -= 10;
			
		switch (Territory_Detected->TerritoryIndex)
		{
		case 1:
			GameStateServer->SetLifeTerritory1(Territory_Detected->Life);
			break;
		case 2:
			GameStateServer->SetLifeTerritory2(Territory_Detected->Life);
			break;
		case 3:
			GameStateServer->SetLifeTerritory3(Territory_Detected->Life);
			break;
		case 4:
			GameStateServer->SetLifeTerritory4(Territory_Detected->Life);
			break;
		default:
			break;
		}
		if (Territory_Detected->Life <= 0)
		{
			Territory_Detected->Life = 100;
			switch (Territory_Detected->TerritoryIndex)
			{
			case 1:
				GameStateServer->SetOwnerTerritory1(ETeam::Clients);
				GameStateServer->SetLifeTerritory1(Territory_Detected->Life);
				break;
			case 2:
				GameStateServer->SetOwnerTerritory2(ETeam::Clients);
				GameStateServer->SetLifeTerritory2(Territory_Detected->Life);
				break;
			case 3:
				GameStateServer->SetOwnerTerritory3(ETeam::Clients);
				GameStateServer->SetLifeTerritory3(Territory_Detected->Life);
				break;
			case 4:
				GameStateServer->SetOwnerTerritory4(ETeam::Clients);
				GameStateServer->SetLifeTerritory4(Territory_Detected->Life);
				break;
			default:
				break;
			}
			Territory_Detected->IsBlocked = true;
			EnableObjectivePoints(Territory_Detected->TerritoryIndex,Territory_Detected->IsBlocked);
			GetWorldTimerManager().SetTimer(Territory_Detected->Timer, Territory_Detected, &AObjectiveNPC::GameTimer, 5, false);
		}
	}
}
void ADevLopWarGameMode::DetectObjectivePoints()
{
	UWorld* World = GetWorld();
	check(World);

	if (GetLocalRole() == ROLE_Authority)
	{
		for (TActorIterator<AObjectiveNPC> It(World); It; ++It)
		{
			if (AObjectiveNPC* Objetivo = Cast<AObjectiveNPC>(*It))
			{
				if (IsValid(Objetivo))
				{
					switch (Objetivo->TerritoryIndex)
					{
					case 1:
						GameStateServer->SetLifeTerritory1(Objetivo->Life);
						GameStateServer->SetOwnerTerritory1(Objetivo->TeamTerritory);
						GameStateServer->SetBlockTerritory1(Objetivo->IsBlocked);
						break;
					case 2:
						GameStateServer->SetLifeTerritory2(Objetivo->Life);
						GameStateServer->SetOwnerTerritory2(Objetivo->TeamTerritory);
						GameStateServer->SetBlockTerritory2(Objetivo->IsBlocked);
						break;
					case 3:
						GameStateServer->SetLifeTerritory3(Objetivo->Life);
						GameStateServer->SetOwnerTerritory3(Objetivo->TeamTerritory);
						GameStateServer->SetBlockTerritory3(Objetivo->IsBlocked);
						break;
					case 4:
						GameStateServer->SetLifeTerritory4(Objetivo->Life);
						GameStateServer->SetOwnerTerritory4(Objetivo->TeamTerritory);
						GameStateServer->SetBlockTerritory4(Objetivo->IsBlocked);
						break;
					default:
						break;
					}
				}
			}
		}
	}
}

void ADevLopWarGameMode::ReturnLobby_Implementation()
{
	GetWorld()->ServerTravel("/Game/Maps/LobbyRoom?listen");
}

void ADevLopWarGameMode::EnableObjectivePoints_Implementation(int IndexObjetivo, bool BlockState)
{
	switch (IndexObjetivo)
	{
	case 1:
		GameStateServer->SetBlockTerritory1(BlockState);
		break;
	case 2:
		GameStateServer->SetBlockTerritory2(BlockState);
		break;
	case 3:
		GameStateServer->SetBlockTerritory3(BlockState);
		break;
	case 4:
		GameStateServer->SetBlockTerritory4(BlockState);
		break;
	default:
		break;
	}
}
