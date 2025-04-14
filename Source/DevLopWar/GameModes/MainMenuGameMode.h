

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OnlineSessionSettings.h"
#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "DevLopWar/Structs/Struct.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Containers/UnrealString.h" 
#include "DevLopWar/Huds/BaseHudMainMenu.h"
#include "Engine/Engine.h"
#include "MainMenuGameMode.generated.h"

UCLASS()
class DEVLOPWAR_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

	AMainMenuGameMode();
public:
	UPROPERTY(BlueprintReadOnly)
	TArray<FRoom> CreateRoomData;
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void CreateHostRoom(int32 PlayerNumber,int32 ChosenMaps,FString RoomName);
	UFUNCTION(BlueprintCallable)
	void FindHostRoom(FString ChosenIP, int ChosenPort,bool Lan);
	UFUNCTION(BlueprintCallable)
	void LogoutPlayer(APlayerController* Controller);
		
	UFUNCTION(BlueprintCallable)
	void CreateRoomID(FName Session,int32 SearchID);
	UFUNCTION()
	void ReturnDeletedRoomData(FCallbackParametros CallbackParams);
	
	UFUNCTION(BlueprintCallable)
	void ReturnRoomData(FCallbackParametros CallbackParams);
	UFUNCTION(BlueprintCallable)
	void EnterLobbyMap(bool Connected);
	
	UFUNCTION()
	void OnFindSessionsComplete(bool Connected);
	
	void ConnectHostRoom(const FOnlineSessionSearchResult& SearchResult);

	void HandleJoinSession(FName SessionName);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	
	FString GetStringFromConnectionState(ESocketConnectionState ConnectionState);
		
	UPROPERTY(BlueprintReadWrite)
	ABaseHudMainMenu* DetectedHud;

	FSocket* UDPSocket;
	
	const TCHAR* IPAddress ;
	FString IPAddressRaw ;
	
	int Port = 7777;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


private:
	UPROPERTY()
	UDevLopWarGameInstance* GameInstance;
	
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;
	
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
	TArray<FOnlineSessionSearchResult> FoundSessions;
	FOnlineSessionSettings SessionSettings;
};
