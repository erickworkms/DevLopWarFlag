
#include "DevLopWar/GameModes/DevLopWarGameMode.h"
#include "DevLopWar/PlayerStates/DevOpPlayerState.h"
#include "UObject/ConstructorHelpers.h"

void ADevLopWarGameMode::ChangeNumDeadZombies_Implementation(int32 Index)
{
	if (IsValid(PlayerRoom[Index]))
	{
		ADevOpPlayerState* PlayerState = Cast<ADevOpPlayerState>(PlayerRoom[Index]->PlayerState);
		if (IsValid(PlayerState))
		{
			GameplayInformation[Index].NumDeadZombies++;
			PlayerState->SetDeadZombiesNum(GameplayInformation[Index].NumDeadZombies);
		}
	}
}

void ADevLopWarGameMode::ChangeNumDeadPlayers_Implementation(int32 Index)
{
	if (IsValid(PlayerRoom[Index]))
	{
		ADevOpPlayerState* PlayerState = Cast<ADevOpPlayerState>(PlayerRoom[Index]->PlayerState);
		if (IsValid(PlayerState))
		{
			GameplayInformation[Index].NumDeadPlayers++;
			PlayerState->SetDeadPlayerNumber(GameplayInformation[Index].NumDeadPlayers);
		}
	}
}

void ADevLopWarGameMode::ChangeNumDeaths_Implementation(int32 Index)
{
	if (IsValid(PlayerRoom[Index]))
	{
		ADevOpPlayerState* PlayerStateLocal = Cast<ADevOpPlayerState>(PlayerRoom[Index]->PlayerState);
		if (IsValid(PlayerStateLocal))
		{
			GameplayInformation[Index].NumDeaths++;
			PlayerStateLocal->SetDeathNumber(GameplayInformation[Index].NumDeaths);
		}
	}
}

void ADevLopWarGameMode::ChangeChosenTeam_Implementation(int32 Index,ETeam Time)
{
	if (IsValid(PlayerRoom[Index]))
	{
		ADevOpPlayerState* PlayerState = Cast<ADevOpPlayerState>(PlayerRoom[Index]);
		if (IsValid(PlayerState))
		{
			GameplayInformation[Index].ChosenTeam = Time;
			PlayerState->SetChosenTeam(GameplayInformation[Index].ChosenTeam);
		}
	}
}

void ADevLopWarGameMode::ChangeTeamFlagOwner_Implementation(ETeam Team)
{
	if (IsValid(GameStateServer))
	{
		if (Team == ETeam::Clients)
		{
			Team = ETeam::Agile;
		}
		TeamFlagOwner = Team;
		GameStateServer->SetTeamFlagOwner(Team);
	}
}
