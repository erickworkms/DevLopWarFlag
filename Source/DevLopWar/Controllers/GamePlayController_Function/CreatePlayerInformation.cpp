

#include "DevLopWar/GameModes/DevLopWarGameMode.h"
#include "DevLopWar/Structs/Struct.h"
#include "Delegates/DelegateSignatureImpl.inl"

void AGamePlayController::AddDataInstanceServer_Implementation()
{
	AddPlayerListServer(this,CreatePlayerInformation(),ReturnPlayerIndex());
}

FPlayerGameplayInformation AGamePlayController::CreatePlayerInformation()
{
	UDevLopWarGameInstance* PlayerInstance = Cast<UDevLopWarGameInstance>(GetGameInstance());
	FPlayerGameplayInformation GameplayInformation;
	GameplayInformation.NumDeadZombies = 0;
	GameplayInformation.NumDeadPlayers = 0;
	GameplayInformation.NumDeaths = 0;
	GameplayInformation.ChosenTeam = PlayerInstance->Team;
	return GameplayInformation;
}
int AGamePlayController::ReturnPlayerIndex()
{
	UDevLopWarGameInstance* PlayerInstance = Cast<UDevLopWarGameInstance>(GetGameInstance());
	return PlayerInstance->PlayerIndex;
}
void AGamePlayController::AddPlayerListServer_Implementation(AGamePlayController* Controller,FPlayerGameplayInformation GameplayInformation,int PlayerIndex)
{
	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();

	if (IsValid(GameMode))
	{
		ADevLopWarGameMode* DevGameMode = Cast<ADevLopWarGameMode>(GameMode);
		if (IsValid(DevGameMode))
		{
			//UDevLopWarGameInstance* PlayerInstance = Cast<UDevLopWarGameInstance>(GetGameInstance());
			DevGameMode->CreatePlayerInformationServer(Controller,GameplayInformation,PlayerIndex);
			CheckInstanceData(GameplayInformation);
		}
	}
}