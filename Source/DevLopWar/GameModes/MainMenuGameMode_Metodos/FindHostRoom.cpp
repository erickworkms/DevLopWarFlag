#include "OnlineSessionSettings.h"
#include "IPAddress.h"
#include "Containers/UnrealString.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/GameModes/MainMenuGameMode.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuGameMode::FindHostRoom(FString ChosenIP, int ChosenPort, bool Lan)
{
	IPAddress = *ChosenIP;
	Port = ChosenPort;
	IPAddressRaw = ChosenIP+":"+FString::FromInt(ChosenPort);
	
	if (Lan)
	{
		FString ServerAddress = IPAddressRaw;// TEXT("127.0.0.1:7777"); 
		UGameplayStatics::OpenLevel(GetWorld(), FName(*ServerAddress), true);
	}
}

void AMainMenuGameMode::OnFindSessionsComplete(bool Connected)
{
	if (Connected)
	{
		FoundSessions = SessionSearch->SearchResults;
		if (SessionSearch->SearchResults.Num() > 0)
		{
			ConnectHostRoom(SessionSearch->SearchResults[0]);
		}
	}
	else
	{
	}
}

FString AMainMenuGameMode::GetStringFromConnectionState(ESocketConnectionState ConnectionState)
{
	switch (ConnectionState)
	{
	case SCS_NotConnected:
		return TEXT("Not Connected");
	case SCS_Connected:
		return TEXT("Connected");
	case SCS_ConnectionError:
		return TEXT("Connection Error");
	default:
		return TEXT("Unknown Error");
	}
}
