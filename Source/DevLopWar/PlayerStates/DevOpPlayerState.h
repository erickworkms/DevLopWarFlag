

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DevLopWar/Structs/Struct.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevOpPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API ADevOpPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated)
	APlayerController* PlayerRoom;
	UPROPERTY(Replicated)
	int32 PlayerIndex;
	UPROPERTY(Replicated)
	ETeam Team;
	
	
	UFUNCTION(BlueprintCallable)
	int32 GetDeadZombiesNum();
	UFUNCTION(Reliable,Client)
	void SetDeadZombiesNum(int32 DeadZombiesNumSet);
	UFUNCTION(BlueprintCallable)
	int32 GetDeadPlayerNumber();
	UFUNCTION(Reliable,Client)
	void SetDeadPlayerNumber(int32 DeadPlayerNumberSet);
	UFUNCTION(BlueprintCallable)
	int32 GetDeathNumber();
	UFUNCTION(Reliable,Client)
	void SetDeathNumber(int32 DeathNumberSet);
	UFUNCTION(BlueprintCallable)
	ETeam GetChosenTeam();
	UFUNCTION(Reliable,Client)
	void SetChosenTeam(ETeam ChosenTeamSet);
	UFUNCTION(BlueprintCallable)
	ETeam GetTeamFlagOwner();
	UFUNCTION(Reliable,Client)
	void SetTeamFlagOwner(ETeam ChosenTeamSet);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(ReplicatedUsing=SetDeadZombiesNum)
	int32 NumDeadZombies;
	UPROPERTY(ReplicatedUsing=SetDeadPlayerNumber)
	int32 NumDeadPlayers;
	UPROPERTY(ReplicatedUsing=SetDeathNumber)
	int32 NumDeaths;
	UPROPERTY(ReplicatedUsing=SetChosenTeam)
	ETeam ChosenTeam;
	UPROPERTY(ReplicatedUsing=SetTeamFlagOwner)
	ETeam TeamFlagOwner = ETeam::NoJob;
};
