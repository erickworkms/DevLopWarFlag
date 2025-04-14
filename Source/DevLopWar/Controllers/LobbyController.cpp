


#include "LobbyController.h"
#include "DevLopWar/GameModes/LobbyGameMode.h"
#include "DevLopWar/PlayerStates/DevOpPlayerState.h"
#include "Net/UnrealNetwork.h"

void ALobbyController::SendMessageServer_Implementation(const FString& name, const FString& Message)
{
	if (HasAuthority()) 
	{
		ALobbyGameMode* GameMode = GetWorld()->GetAuthGameMode<ALobbyGameMode>();
		if (GameMode != nullptr)
		{
			GameMode->SendMessageChat(Message);
		}
	}
}

void ALobbyController::SendMessageClient_Implementation(const FString& name, const FString& Message)
{
	HudChat->SendMessageChat(Message);
}

void ALobbyController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

ALobbyController::ALobbyController()
{
	PlayerState = GetPlayerState<ADevOpPlayerState>();
	bReplicates = true;
}

void ALobbyController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	UDevLopWarGameInstance* PlayerInstance = Cast<UDevLopWarGameInstance>(GetGameInstance());
	SetUser(PlayerInstance->PlayerName);
}

void ALobbyController::AddDataInstance_Implementation(int32 PlayerIndex)
{
	UDevLopWarGameInstance* PlayerInstance = Cast<UDevLopWarGameInstance>(GetGameInstance());
	PlayerInstance->PlayerController = this;
	PlayerInstance->PlayerIndex = PlayerIndex;
	PlayerInstance->Team = ETeam::Agile;
}

FString ALobbyController::GetUser() const
{
	return User;
}

void ALobbyController::SetUser_Implementation(const FString& UserSet)
{
	User = UserSet;
}

void ALobbyController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALobbyController, HudChat);
	DOREPLIFETIME(ALobbyController, User);
}

void ALobbyController::CheckEntryLogin_Implementation(const TArray<FString>& PlayerRoomName)
{
	if (IsValid(HudChat))
	{
		HudChat->AddHudRooms(PlayerRoomName);
	}
}
