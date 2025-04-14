
#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "JsonObjectConverter.h"
#include "OnlineSubsystemClasses.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/GameModes/MainMenuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"

#define SETTING_MAPNAME FName(TEXT("MAPNAME"))

void AMainMenuGameMode::CreateHostRoom(int32 PlayerNumber,int32 ChosenMaps,FString RoomName)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionInt = OnlineSubsystem->GetSessionInterface();

		if (SessionInt.IsValid())
		{
			SessionSettings.bIsLANMatch = false;
			SessionSettings.BuildUniqueId = true;
			SessionSettings.bUsesPresence = true;
			SessionSettings.bUsesStats = true;
			SessionSettings.bIsDedicated = false;
			SessionSettings.NumPublicConnections = PlayerNumber;
			SessionSettings.NumPrivateConnections = 0;
			SessionSettings.bAllowInvites = true;
			SessionSettings.bAllowJoinInProgress = true;
			SessionSettings.bShouldAdvertise = true;
			SessionSettings.bAllowJoinViaPresence = true;
			SessionSettings.bAllowJoinViaPresenceFriendsOnly = true;
			SessionSettings.Settings.Add(FName(TEXT("SessionName")), FVariantData(RoomName));
			SessionSettings.Set(NAME_GameSession, FString(RoomName));
			
			switch (ChosenMaps)
			{
			case 0:
				SessionSettings.Set(SETTING_MAPNAME, FString("/Game/Maps/GameplayMap"));
				break;
			case 1:
				SessionSettings.Set(SETTING_MAPNAME, FString("/Game/Maps/GameplayMap"));
				break;
			case 2:
				SessionSettings.Set(SETTING_MAPNAME, FString("/Game/Maps/GameplayMap"));
				break;
			default:
				SessionSettings.Set(SETTING_MAPNAME, FString("/Game/Maps/GameplayMap"));
				break;
			}

			SessionInt->CreateSession(0, FName(*RoomName), SessionSettings);
			GameInstance->SessionSettings = SessionSettings;
			GameInstance->SessionInt = SessionInt;
			FNamedOnlineSession* SessionData = SessionInt->GetNamedSession(*RoomName);
			FRoom Data;
			Data.idRoom = SessionData->GetSessionIdStr();
			Data.RoomName = RoomName;
			Data.MapIndex = FString::FromInt(ChosenMaps);
			Data.Map = "Map" + FString::FromInt(ChosenMaps);
			Data.CreatedUser = GameInstance->PlayerName;
			//APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			//Data.IP = "192.168.15.180";
			//Data.IP = PlayerController->GetNetConnection()->RemoteAddressToString();
			Data.IP = GameInstance->ip;

			Data.Lan = UKismetStringLibrary::Conv_BoolToString(SessionSettings.bIsLANMatch);
			Data.ActivatedPlayerNumber = FString::FromInt(1);
			Data.ActivatedPlayerTotal = FString::FromInt(PlayerNumber);
			Data.DedicatedServer = UKismetStringLibrary::Conv_BoolToString(SessionSettings.bIsDedicated);

			EnterLobbyMap(true);
			//SaveRoomData(Data);
		}
	}
}

void AMainMenuGameMode::ReturnDeletedRoomData(FCallbackParametros CallbackParams)
{
	if (CallbackParams.IsConnected)
	{
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,"Failed to create a new room");
	}
}


void AMainMenuGameMode::EnterLobbyMap(bool Connected)
{
	if (Connected)
	{
		GetWorld()->ServerTravel("/Game/Maps/LobbyMap?listen");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,"Failed to create a new room");
	}
}

void AMainMenuGameMode::ReturnRoomData(FCallbackParametros CallbackParams)
{
	if (CallbackParams.IsConnected)
	{
		if (FJsonObjectConverter::JsonArrayStringToUStruct(CallbackParams.DataResponse.ResponseContent, &CreateRoomData, 0, 0))
		{
			DetectedHud->OnFindSessionsComplete(true);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Failed");
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,"Failed");
	}
}