

#pragma once

#include "CoreMinimal.h"
#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "GameFramework/GameModeBase.h"
#include "..\Huds\BaseHudMainMenu.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "DevLopWar/Structs/Struct.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/Controllers/LobbyController.h"
#include "LobbyGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerJoinedDelegate, APlayerController*, NewPlayer);

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

	ALobbyGameMode();

public:
	UPROPERTY(Replicated, BlueprintReadWrite)
	TArray<APlayerController*> PlayerRoom;

	UPROPERTY(Replicated,BlueprintReadOnly)
	TArray<FString> PlayerRoomName;

	UPROPERTY(BlueprintReadOnly)
	TArray<FRoom> CreateRoomData;

	UPROPERTY(BlueprintReadWrite)
	bool IsGameInitialized = false;

	UPROPERTY(BlueprintReadWrite)
	ABaseHudMainMenu* DetectedHud;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Teams")
	TArray<FPlayerInformation> Players;
	
	virtual void BeginPlay() override;

	FOnPlayerJoinedDelegate OnPlayerJoined;

	UFUNCTION()
	virtual void PostLogin(APlayerController* NewPlayer) override;
	
	UFUNCTION(BlueprintCallable)
	void StartGame();

	UFUNCTION(BlueprintCallable)
	void CheckEntryLogin();

	virtual void Logout(AController* Exiting) override;

	UFUNCTION()
	void HandlePlayerJoined(APlayerController* PlayerController);
	
	UFUNCTION()
	void ControllerDelay(ALobbyController* Controller, APlayerController* NewPlayer);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SendMessageChat(const FString& Message);

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void DisconnectClient(APlayerController* PlayerController, int32 Id);

	UFUNCTION(BlueprintCallable)
	void DeletedRoom();
	
	UFUNCTION()
	void TimerHud();

	UFUNCTION(BlueprintCallable,Reliable,Server)
	void UpdatePlayerList();

	UPROPERTY()
	int ValueIndexUserDelay=0;

	FTimerHandle Timer;
	
	bool CheckLobbyBegin = false;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
	UPROPERTY()
	UDevLopWarGameInstance* GameInstance;
};
