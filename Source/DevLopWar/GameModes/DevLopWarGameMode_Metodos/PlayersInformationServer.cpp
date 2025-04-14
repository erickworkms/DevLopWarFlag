

#include "DevLopWar/Controllers/GamePlayController.h"
#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "DevLopWar/GameModes/DevLopWarGameMode.h"
#include "DevLopWar/PlayerStates/DevOpPlayerState.h"
#include "UObject/ConstructorHelpers.h"

void ADevLopWarGameMode::GetTeamInformations(TArray<APlayerController*> PlayersList)
{
	for (int i=0;i < PlayersList.Num();i++)
	{
		ADevOpPlayerState* PlayerState = Cast<ADevOpPlayerState>(PlayersList[i]);
		FPlayerGameplayInformation InfAux;
		InfAux.NumDeadZombies = PlayerState->GetDeadZombiesNum();
		InfAux.NumDeadPlayers = PlayerState->GetDeadPlayerNumber();
		InfAux.NumDeaths = PlayerState->GetDeathNumber();
		InfAux.ChosenTeam = PlayerState->GetChosenTeam();
		GameplayInformation.Add(InfAux);
	}
}

ETeam ADevLopWarGameMode::GetFlagTeamOwner()
{
	return TeamFlagOwner;
}

void ADevLopWarGameMode::ChangeTeamPoints_Implementation(ETeam Team)
{
	switch (Team)
	{
		case ETeam::Cascade:
			CascadeTeam++;
			break;
		case ETeam::Agile:
			AgileTeam++;
			break;
		default:
			break;
	}
	GameStateServer->SetCascadePoints(CascadeTeam);
	GameStateServer->SetAgilePoints(AgileTeam);
}


void ADevLopWarGameMode::CreatePlayerInformationServer_Implementation(AGamePlayController* Controller,FPlayerGameplayInformation GameplayInformationLocal,int PlayerIndex)
{
	PlayerRoom[PlayerIndex] = Controller;
	GameplayInformation[PlayerIndex] = GameplayInformationLocal;
}
