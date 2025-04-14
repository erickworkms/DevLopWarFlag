
#include "DevLopWar/GameModes/DevLopWarGameMode.h"
#include "UObject/ConstructorHelpers.h"

void ADevLopWarGameMode::AddPlayerTeam(const FString& PlayerName, const ETeam& Team)
{
	FPlayerInformation dados;
	dados.Name = PlayerName;
	dados.Team = Team;
	Players.Add(dados);
}

void ADevLopWarGameMode::RemovePlayerTeam(const FString& PlayerName)
{
	for (int32 i = 0; i < Players.Num(); ++i)
	{
		if (Players[i].Name.Equals(PlayerName, ESearchCase::IgnoreCase))
		{
			Players.RemoveAt(i);
			break;
		}
	}
}