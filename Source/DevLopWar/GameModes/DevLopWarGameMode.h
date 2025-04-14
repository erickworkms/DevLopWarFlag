

#pragma once

#include "CoreMinimal.h"
#include "DevLopWar/Structs/Struct.h"
#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "DevLopWar/PlayerStates/DevLopWarGameStateBase.h"
#include "GameFramework/GameModeBase.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/Controllers/GamePlayController.h"
#include "../Characters/NPC/NPCObjective.h"
#include "DevLopWarGameMode.generated.h"

UCLASS(minimalapi)
class ADevLopWarGameMode : public AGameModeBase
{
	GENERATED_BODY()
	ADevLopWarGameMode();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Teams")
	TArray<FPlayerInformation> Players;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Teams")
	TArray<FPlayerGameplayInformation> GameplayInformation;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<APlayerController*> PlayerRoom;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> PlayerRoomName;

	UPROPERTY(BlueprintReadOnly)
	TArray<FRoom> CreateRoomData;

	UPROPERTY()
	ETeam TeamFlagOwner = ETeam::NoJob;

	UFUNCTION()
	int ReturnPlayerIndex(AGamePlayController* Controller);

	FTimerHandle Timer;

	TArray<FTimerHandle> ReviverTimer;

	virtual void BeginPlay() override;

	virtual void Logout(AController* Exiting) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	void AddPlayerTeam(const FString& PlayerName,const ETeam& Team);
	UFUNCTION(BlueprintCallable)
	void RemovePlayerTeam(const FString& PlayerName);
	UFUNCTION(BlueprintCallable)
	void GetTeamInformations(TArray<APlayerController*> PlayersList);
	
	UFUNCTION(Reliable,Server)
	void ChangeNumDeadZombies(int32 Index);
	UFUNCTION(Reliable,Server)
	void ChangeNumDeadPlayers(int32 Index);
	UFUNCTION(Reliable,Server)
	void ChangeNumDeaths(int32 Index);
	UFUNCTION(Reliable,Server)
	void ChangeChosenTeam(int32 Index,ETeam Team);

	UFUNCTION()
	ETeam GetFlagTeamOwner();

	UFUNCTION(Reliable,Server)
	void ChangeTeamFlagOwner(ETeam Team);

	UFUNCTION(Reliable,Server)
	void ChangeTeamPoints(ETeam Team);
		
	UFUNCTION(Reliable,Server)
	void AttackDamageProjectile(AActor* OwnerProjetil,AActor* DetectedEnemy,AActor* Projetil);

	UFUNCTION(Reliable,Server)
	void CreatePlayerInformationServer(AGamePlayController* Controller,FPlayerGameplayInformation GameplayInformationLocal,int PlayerIndex);

	UFUNCTION(Reliable,Server)
	void EnableObjectivePoints(int IndexObjetivo,bool BlockState);

	UFUNCTION(BlueprintCallable,Reliable,Server)
	void ReturnLobby();

	UFUNCTION(Reliable,Server)
	void UpdateTerritoryNPCDamage(AObjectiveNPC* Territory_Detected);

private:
	UPROPERTY()
	float GameplayTime = 300;

	UPROPERTY()
	bool GameEnd = false;

	UPROPERTY()
	int32 AgileTeam = 0;

	UPROPERTY()
	int32 CascadeTeam = 0;

	

	UPROPERTY()
	UDevLopWarGameInstance* GameInstance;
		
	UPROPERTY()
	ADevLopWarGameStateBase* GameStateServer;

	UFUNCTION(BlueprintCallable)
	void DetectObjectivePoints();
		
	UFUNCTION(Reliable,Server)
	void GameTimer();
};



