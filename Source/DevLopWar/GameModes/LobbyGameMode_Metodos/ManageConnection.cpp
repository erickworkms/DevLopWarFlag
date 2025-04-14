

#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/Controllers/LobbyController.h"
#include "DevLopWar/GameModes/LobbyGameMode.h"
#include "Kismet/GameplayStatics.h"

void ALobbyGameMode::DisconnectClient_Implementation(APlayerController* PlayerController, int32 Id)
{
	if (IsValid(PlayerRoom[Id]) && GetLocalRole() == ROLE_Authority)
	{
		PlayerRoom[Id]->ClientTravel("/Game/Maps/StartScreen", ETravelType::TRAVEL_Absolute);
		PlayerRoom.RemoveAt(Id);
		PlayerRoomName.RemoveAt(Id);
	}
	for (int i=0;i < PlayerRoom.Num();i++)
	{
		if (IsValid(PlayerRoom[i]))
		{
			ALobbyController* Controller = Cast<ALobbyController>(PlayerRoom[i]);
			Controller->CheckEntryLogin(PlayerRoomName);
		}
	}
}

bool ALobbyGameMode::DisconnectClient_Validate(APlayerController* PlayerController, int32 Id)
{
	if (Id == 0 && GetLocalRole() == ROLE_Authority)
	{
		APlayerController* DefaultPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		DefaultPlayerController->ClientTravel("/Game/Maps/StartScreen", ETravelType::TRAVEL_Absolute);
	}
	else if (IsValid(PlayerRoom[Id]) && GetLocalRole() == ROLE_Authority)
	{
		return true;
	}
	return false;
}

void ALobbyGameMode::DeletedRoom()
{
	if (GameInstance->SessionInt.IsValid())
	{
		FString RoomName;
		GameInstance->SessionSettings.Get(NAME_GameSession, RoomName);
		GameInstance->SessionInt->DestroySession(*RoomName);
	}
}