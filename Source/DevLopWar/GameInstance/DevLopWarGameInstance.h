

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "DevLopWar/Structs/Struct.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWarGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API UDevLopWarGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated)
	APlayerController* PlayerController;
	
	UPROPERTY(Replicated,BlueprintReadWrite)
	int32 PlayerIndex;
	
	UPROPERTY(Replicated,BlueprintReadWrite)
	ETeam Team;
	
	UPROPERTY(BlueprintReadWrite)
	FString token;

	UPROPERTY(BlueprintReadWrite)
	FString ip;
	
	UPROPERTY(BlueprintReadWrite)
	FString PlayerName = "Server";

	UPROPERTY(BlueprintReadOnly)
	TArray<FRoom> CreateRoomData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Teams")
	TArray<FPlayerInformation> Players;

	UPROPERTY(BlueprintReadWrite)
	TArray<APlayerController*> PlayerRoom;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> PlayerRoomName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Teams")
	int32 TotalPlayersNumber;
	
	FOnlineSessionSettings SessionSettings;
	IOnlineSessionPtr SessionInt;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
