
#include "DevOpPlayerState.h"

#include "Net/UnrealNetwork.h"

void ADevOpPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADevOpPlayerState,NumDeadZombies);
	DOREPLIFETIME(ADevOpPlayerState,NumDeadPlayers);
	DOREPLIFETIME(ADevOpPlayerState,NumDeaths);
	DOREPLIFETIME(ADevOpPlayerState,ChosenTeam);
	DOREPLIFETIME(ADevOpPlayerState,PlayerRoom);
	DOREPLIFETIME(ADevOpPlayerState,PlayerIndex);
	DOREPLIFETIME(ADevOpPlayerState,Team);
	DOREPLIFETIME(ADevOpPlayerState,TeamFlagOwner);
}

int32 ADevOpPlayerState::GetDeadZombiesNum() 
{
	return NumDeadZombies;
}

void ADevOpPlayerState::SetDeadZombiesNum_Implementation(int32 DeadZombiesNumSet)
{
	NumDeadZombies = DeadZombiesNumSet;
}

int32 ADevOpPlayerState::GetDeadPlayerNumber() 
{
	return NumDeadPlayers;
}

void ADevOpPlayerState::SetDeadPlayerNumber_Implementation(int32 DeadPlayerNumberSet)
{
	NumDeadPlayers = DeadPlayerNumberSet;
}

int32 ADevOpPlayerState::GetDeathNumber() 
{
	return NumDeaths;
}

void ADevOpPlayerState::SetDeathNumber_Implementation(int32 DeathNumberSet)
{
	NumDeaths = DeathNumberSet;
}

ETeam ADevOpPlayerState::GetChosenTeam() 
{
	return ChosenTeam;
}

ETeam ADevOpPlayerState::GetTeamFlagOwner()
{
	return TeamFlagOwner;
}

void ADevOpPlayerState::SetTeamFlagOwner_Implementation(ETeam TeamFlagOwnerSet)
{
	TeamFlagOwner = TeamFlagOwnerSet;
}

void ADevOpPlayerState::SetChosenTeam_Implementation(ETeam ChosenTeamSet)
{
	this->ChosenTeam = ChosenTeamSet;
}
