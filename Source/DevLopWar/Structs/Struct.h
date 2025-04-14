#pragma once

#include "Struct.generated.h"

USTRUCT(BlueprintType)
struct FHttpResponseData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	int32 StatusCode;

	UPROPERTY(BlueprintReadOnly)
	FString ResponseContent;
};


USTRUCT(BlueprintType)
struct FCallbackParametros
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	bool IsConnected;

	UPROPERTY(BlueprintReadOnly)
	FHttpResponseData DataResponse;
};

UENUM(BlueprintType)
enum class ETeam : uint8
{
	Clients,
	Agile,
	Cascade,
	NoJob
};
UENUM(BlueprintType)
enum class EMap : uint8
{
	Map1,
	Map2,
	Map3,
};
USTRUCT(BlueprintType)
struct FPlayerInformation
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Player")
	FString Name;

	UPROPERTY(BlueprintReadWrite, Category = "Player")
	ETeam Team;
};
USTRUCT(BlueprintType)
struct FPlayerGameplayInformation
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Player")
	int32 NumDeadZombies;
	UPROPERTY(BlueprintReadWrite, Category = "Player")
	int32 NumDeadPlayers;
	UPROPERTY(BlueprintReadWrite, Category = "Player")
	int32 NumDeaths;
	UPROPERTY(BlueprintReadWrite, Category = "Player")
	ETeam ChosenTeam;
};
USTRUCT(BlueprintType)
struct FRoom
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString idRoom;
	
	UPROPERTY(BlueprintReadWrite)
	FString RoomName;

	UPROPERTY(BlueprintReadWrite)
	FString MapIndex;

	UPROPERTY(BlueprintReadWrite)
	FString Map;
	
	UPROPERTY(BlueprintReadWrite)
	FString IP;

	UPROPERTY(BlueprintReadWrite)
	FString Lan;

	UPROPERTY(BlueprintReadWrite)
	FString ActivatedPlayerNumber;

	UPROPERTY(BlueprintReadWrite)
	FString ActivatedPlayerTotal;

	UPROPERTY(BlueprintReadWrite)
	FString DedicatedServer;

	UPROPERTY(BlueprintReadWrite)
	FString CreatedUser;
};

