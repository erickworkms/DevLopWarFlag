#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "..\MainMenuGameMode.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuGameMode::ConnectHostRoom(const FOnlineSessionSearchResult& SearchResult)
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();

		if (SessionInterface.IsValid())
		{			
			OnJoinSessionCompleteDelegate.BindUObject(this, &AMainMenuGameMode::OnJoinSessionComplete);
			SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);
			SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
			SessionInterface->JoinSession(0, "SessionName", SearchResult);
		}
	}
}
void AMainMenuGameMode::CreateRoomID(FName Session,int32 SearchID)
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			OnJoinSessionCompleteDelegate.BindUObject(this, &AMainMenuGameMode::OnJoinSessionComplete);
			SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);
			SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
			SessionInterface->JoinSession(0, Session, SessionSearch->SearchResults[SearchID]);
		}
	}
}

void AMainMenuGameMode::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{	
	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		HandleJoinSession(SessionName);
	}
	else
	{
	
	}
	
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);
		}
	}
}


void AMainMenuGameMode::HandleJoinSession(FName SessionName)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->ClientTravel(IPAddressRaw, ETravelType::TRAVEL_Absolute);
}
