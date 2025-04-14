
#include "DevLopWarGameStateBase.h"
#include "DevLopWar/Structs/Struct.h"
#include "Net/UnrealNetwork.h"

ADevLopWarGameStateBase::ADevLopWarGameStateBase()
{
}

void ADevLopWarGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADevLopWarGameStateBase, GameplayTime);
	DOREPLIFETIME(ADevLopWarGameStateBase, LifeTerritory1);
	DOREPLIFETIME(ADevLopWarGameStateBase, LifeTerritory2);
	DOREPLIFETIME(ADevLopWarGameStateBase, LifeTerritory3);
	DOREPLIFETIME(ADevLopWarGameStateBase, LifeTerritory4);
	DOREPLIFETIME(ADevLopWarGameStateBase, OwnerTerritory1);
	DOREPLIFETIME(ADevLopWarGameStateBase, OwnerTerritory2);
	DOREPLIFETIME(ADevLopWarGameStateBase, OwnerTerritory3);
	DOREPLIFETIME(ADevLopWarGameStateBase, OwnerTerritory4);
	DOREPLIFETIME(ADevLopWarGameStateBase, WinnerTeam);
	DOREPLIFETIME(ADevLopWarGameStateBase, AgilePoints);
	DOREPLIFETIME(ADevLopWarGameStateBase, CascadePoints);
	DOREPLIFETIME(ADevLopWarGameStateBase, TeamFlagOwner);
}

float ADevLopWarGameStateBase::GetGameplayTime()
{
	return GameplayTime;
}

void ADevLopWarGameStateBase::SetGameplayTime_Implementation(float GameplayTimeSet)
{
	GameplayTime = GameplayTimeSet;
}

float ADevLopWarGameStateBase::GetLifeTerritory1()
{
	return LifeTerritory1;
}

void ADevLopWarGameStateBase::SetLifeTerritory1_Implementation(float LifeTerritory1Set)
{
	LifeTerritory1 = LifeTerritory1Set;
}

float ADevLopWarGameStateBase::GetLifeTerritory2()
{
	return LifeTerritory2;
}

void ADevLopWarGameStateBase::SetLifeTerritory2_Implementation(float LifeTerritory2Set)
{
	LifeTerritory2 = LifeTerritory2Set;
}

float ADevLopWarGameStateBase::GetLifeTerritory3()
{
	return LifeTerritory3;
}

void ADevLopWarGameStateBase::SetLifeTerritory3_Implementation(float LifeTerritory3Set)
{
	LifeTerritory3 = LifeTerritory3Set;
}

float ADevLopWarGameStateBase::GetLifeTerritory4()
{
	return LifeTerritory4;
}

void ADevLopWarGameStateBase::SetLifeTerritory4_Implementation(float LifeTerritory4Set)
{
	LifeTerritory4 = LifeTerritory4Set;
}


ETeam ADevLopWarGameStateBase::GetWinnerTeam()
{
	return WinnerTeam;
}

void ADevLopWarGameStateBase::SetWinnerTeam_Implementation(ETeam Winner)
{
	WinnerTeam = Winner;
}

ETeam ADevLopWarGameStateBase::GetOwnerTerritory1()
{
	return OwnerTerritory1;
}

bool ADevLopWarGameStateBase::GetBlockTerritory1()
{
	return BlockTerritory1;
}

void ADevLopWarGameStateBase::SetBlockTerritory1_Implementation(bool BlockTerritory1Set)
{
	BlockTerritory1 = BlockTerritory1Set;
}

bool ADevLopWarGameStateBase::GetBlockTerritory2()
{
	return BlockTerritory2;
}

void ADevLopWarGameStateBase::SetBlockTerritory2_Implementation(bool BlockTerritory2Set)
{
	BlockTerritory2 = BlockTerritory2Set;
}

bool ADevLopWarGameStateBase::GetBlockTerritory3()
{
	return BlockTerritory3;
}

void ADevLopWarGameStateBase::SetBlockTerritory3_Implementation(bool BlockTerritory3Set)
{
	BlockTerritory3 = BlockTerritory3Set;
}

bool ADevLopWarGameStateBase::GetBlockTerritory4()
{
	return BlockTerritory4;
}

void ADevLopWarGameStateBase::SetBlockTerritory4_Implementation(bool BlockTerritory4Set)
{
	BlockTerritory4 = BlockTerritory4Set;
}

void ADevLopWarGameStateBase::SetOwnerTerritory1_Implementation(ETeam OwnerTerritory1Set)
{
	OwnerTerritory1 = OwnerTerritory1Set;
}

ETeam ADevLopWarGameStateBase::GetOwnerTerritory2()
{
	return OwnerTerritory2;
}

void ADevLopWarGameStateBase::SetOwnerTerritory2_Implementation(ETeam OwnerTerritory2Set)
{
	OwnerTerritory2 = OwnerTerritory2Set;
}

ETeam ADevLopWarGameStateBase::GetOwnerTerritory3()
{
	return OwnerTerritory3;
}

void ADevLopWarGameStateBase::SetOwnerTerritory3_Implementation(ETeam OwnerTerritory3Set)
{
	OwnerTerritory3 = OwnerTerritory3Set;
}

ETeam ADevLopWarGameStateBase::GetOwnerTerritory4()
{
	return OwnerTerritory4;
}

void ADevLopWarGameStateBase::SetOwnerTerritory4_Implementation(ETeam OwnerTerritory4Set)
{
	this->OwnerTerritory4 = OwnerTerritory4Set;
}

bool ADevLopWarGameStateBase::GetCheckTakenTerritory(int TerritoryIndex, ETeam TimeAtualSet)
{
	switch (TerritoryIndex)
	{
	case 1:
		if (TimeAtualSet == GetOwnerTerritory1())
		{
			return true;
		}
		return false;
	case 2:
		if (TimeAtualSet == GetOwnerTerritory2())
		{
			return true;
		}
		return false;
	case 3:
		if (TimeAtualSet == GetOwnerTerritory3())
		{
			return true;
		}
		return false;
	case 4:
		if (TimeAtualSet == GetOwnerTerritory4())
		{
			return true;
		}
		return false;
	default:
		return false;
	}
}
int32 ADevLopWarGameStateBase::GetAgilePoints()
{
	return AgilePoints;
}

void ADevLopWarGameStateBase::SetAgilePoints_Implementation(int32 AgilePointsSet)
{
	AgilePoints = AgilePointsSet;
}

int32 ADevLopWarGameStateBase::GetCascadePoints()
{
	return CascadePoints;
}
void ADevLopWarGameStateBase::SetCascadePoints_Implementation(int32 CascadePointsSet)
{
	CascadePoints = CascadePointsSet;
}

ETeam ADevLopWarGameStateBase::GetTeamFlagOwner()
{
	return TeamFlagOwner;
}

void ADevLopWarGameStateBase::SetTeamFlagOwner_Implementation(ETeam ChosenTeamSet)
{
	TeamFlagOwner = ChosenTeamSet;
}

