


#include "LobbyGameMode.h"
#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "GameFramework/HUD.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/Controllers/LobbyController.h"
#include "DevLopWar/PlayerStates/DevOpPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

ALobbyGameMode::ALobbyGameMode()
{
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDClass(TEXT("/Game/Maps/HudLobbyScreen"));
	if (PlayerHUDClass.Succeeded())
	{
		HUDClass = PlayerHUDClass.Class;
	}
	PlayerControllerClass = ALobbyController::StaticClass();
	PlayerStateClass = ADevOpPlayerState::StaticClass();
	bReplicates = true;
}

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* DefaultPlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (DefaultPlayerController)
	{
		DefaultPlayerController->bShowMouseCursor = true;
		DefaultPlayerController->DefaultMouseCursor = EMouseCursor::Crosshairs;

		GameInstance = Cast<UDevLopWarGameInstance>(GetWorld()->GetGameInstance());
		CheckEntryLogin();
	}
	IsGameInitialized = false;
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	ALobbyController* Controller = Cast<ALobbyController>(NewPlayer);

	if (!IsGameInitialized)
	{
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("ControllerDelay"), Controller, NewPlayer);

		FTimerHandle PostLoginTimerHandle;
		GetWorldTimerManager().SetTimer(PostLoginTimerHandle, TimerDelegate, 0.5f, false);
	}
	else
	{
		ControllerDelay(Controller,NewPlayer);
	}
}

void ALobbyGameMode::ControllerDelay(ALobbyController* Controller, APlayerController* NewPlayer)
{
	Controller->AddDataInstance(PlayerRoom.Num());
    
	FPlayerInformation PlayerInformation;
	PlayerInformation.Name = Controller->GetUser();
	PlayerInformation.Team = ETeam::NoJob;
        
	Players.Add(PlayerInformation);
	PlayerRoomName.Add(Controller->GetUser());
	PlayerRoom.Add(NewPlayer);
	OnPlayerJoined.Broadcast(NewPlayer);
}

void ALobbyGameMode::StartGame()
{
	IsGameInitialized = true;

	GameInstance->CreateRoomData = CreateRoomData;
	GameInstance->Players = Players;
	GameInstance->PlayerRoom = PlayerRoom;
	GameInstance->PlayerRoomName = PlayerRoomName;
	GameInstance->TotalPlayersNumber = PlayerRoom.Num();
	GetWorld()->ServerTravel("/Game/Maps/GameplayMap?listen");
}

void ALobbyGameMode::CheckEntryLogin()
{
	OnPlayerJoined.AddDynamic(this, &ALobbyGameMode::HandlePlayerJoined);
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	if (GetLocalRole() == ROLE_Authority && !IsGameInitialized)
	{
		for (int i=0;i < PlayerRoom.Num();i++)
		{
			if (IsValid(PlayerRoom[i]) && PlayerRoom[i] == Exiting)
			{
				PlayerRoomName.RemoveAt(i);
				PlayerRoom.RemoveAt(i);
				Players.RemoveAt(i);
			}
		}
		DetectedHud->AddHudRooms(PlayerRoomName);
	}
}

void ALobbyGameMode::HandlePlayerJoined(APlayerController* PlayerController)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		for (int i=0;i < PlayerRoom.Num();i++)
		{
			if (IsValid(PlayerRoom[i]) && PlayerRoom[i] != PlayerController)
			{
				ALobbyController* Controller = Cast<ALobbyController>(PlayerRoom[i]);
				Controller->CheckEntryLogin(PlayerRoomName);
			}
			else if (IsValid(PlayerRoom[i]) && PlayerRoom[i] == PlayerController)
			{
				ValueIndexUserDelay = i;
				GetWorldTimerManager().SetTimer(Timer, this, &ALobbyGameMode::TimerHud, 0.25f,false);
			}
		}
	}
}

void ALobbyGameMode::TimerHud()
{
	ALobbyController* Controller = Cast<ALobbyController>(PlayerRoom[ValueIndexUserDelay]);
	Controller->CheckEntryLogin(PlayerRoomName);
	GetWorldTimerManager().ClearTimer(Timer);
}

void ALobbyGameMode::UpdatePlayerList_Implementation()
{
	UWorld* World = GetWorld();
	check(World);

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	ALobbyController* Server = Cast<ALobbyController>(Controller);

	//PostLogin(Controller);
	TArray<APlayerController*> PlayersFound;
	PlayersFound.Add(Controller);
	for (FConstControllerIterator it = World->GetControllerIterator(); it; ++it)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(*it))
			if (IsValid(PlayerController))
			{
				ALobbyController* PlayerFound = Cast<ALobbyController>(PlayerController);
					if (Server != PlayerFound)
					{
						PlayersFound.Add(PlayerFound);
					}					
			}
	}
	TArray<FTimerDelegate> TimerDelegate;
	TimerDelegate.SetNum(PlayersFound.Num());
	TArray<FTimerHandle> PostLoginTimerHandle;
	PostLoginTimerHandle.SetNum(PlayersFound.Num());
	for (int i = 0; i < PlayersFound.Num();i++)
	{
		TimerDelegate[i].BindUFunction(this, FName("PostLogin"), PlayersFound[i]);
		GetWorldTimerManager().SetTimer(PostLoginTimerHandle[i], TimerDelegate[i], (0.5f+i)/2, false);
	}
}

void ALobbyGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALobbyGameMode,PlayerRoom);
	DOREPLIFETIME(ALobbyGameMode,PlayerRoomName);
}
