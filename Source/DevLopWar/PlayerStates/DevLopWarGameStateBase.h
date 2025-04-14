

#pragma once

#include "CoreMinimal.h"
#include "DevLopWar/Structs/Struct.h"
#include "GameFramework/GameStateBase.h"
#include "DevLopWarGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API ADevLopWarGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

	ADevLopWarGameStateBase();

public:
	
	UFUNCTION(BlueprintCallable)
	float GetGameplayTime();
	UFUNCTION(Reliable,Server)
	void SetGameplayTime(float GameplayTimeSet);
	
	UFUNCTION(BlueprintCallable)
	float GetLifeTerritory1();
	UFUNCTION(Reliable,Server)
	void SetLifeTerritory1(float LifeTerritory1Set);
	UFUNCTION(BlueprintCallable)
	ETeam GetOwnerTerritory1();
	UFUNCTION(Reliable,Server)
	void SetOwnerTerritory1(ETeam OwnerTerritory1Set);
	UFUNCTION(BlueprintCallable)
	bool GetBlockTerritory1();
	UFUNCTION(Reliable,Server)
	void SetBlockTerritory1(bool BlockTerritory1Set);
	
	
	UFUNCTION(BlueprintCallable)
	float GetLifeTerritory2();
	UFUNCTION(Reliable,Server)
	void SetLifeTerritory2(float LifeTerritory2Set);
	UFUNCTION(BlueprintCallable)
	ETeam GetOwnerTerritory2();
	UFUNCTION(Reliable,Server)
	void SetOwnerTerritory2(ETeam OwnerTerritory2Set);
	UFUNCTION(BlueprintCallable)
	bool GetBlockTerritory2();
	UFUNCTION(Reliable,Server)
	void SetBlockTerritory2(bool BlockTerritory2Set);
	
	UFUNCTION(BlueprintCallable)
	float GetLifeTerritory3();
	UFUNCTION(Reliable,Server)
	void SetLifeTerritory3(float LifeTerritory3Set);
	UFUNCTION(BlueprintCallable)
	ETeam GetOwnerTerritory3();
	UFUNCTION(Reliable,Server)
	void SetOwnerTerritory3(ETeam OwnerTerritory3Set);
	UFUNCTION(BlueprintCallable)
	bool GetBlockTerritory3();
	UFUNCTION(Reliable,Server)
	void SetBlockTerritory3(bool BlockTerritory3Set);
	
	UFUNCTION(BlueprintCallable)
	float GetLifeTerritory4();
	UFUNCTION(Reliable,Server)
	void SetLifeTerritory4(float LifeTerritory4Set);
	UFUNCTION(BlueprintCallable)
	ETeam GetOwnerTerritory4();
	UFUNCTION(Reliable,Server)
	void SetOwnerTerritory4(ETeam OwnerTerritory4Set);
	UFUNCTION(BlueprintCallable)
	bool GetBlockTerritory4();
	UFUNCTION(Reliable,Server)
	void SetBlockTerritory4(bool BlockTerritory4Set);

	UFUNCTION(BlueprintCallable)
	bool GetCheckTakenTerritory(int TerritoryIndex,ETeam TeamAtualSet);
	
	UFUNCTION(BlueprintCallable)
	ETeam GetWinnerTeam();
	UFUNCTION(Reliable,Server)
	void SetWinnerTeam(ETeam Winner);

	UFUNCTION(BlueprintCallable)
	int32 GetAgilePoints();
	UFUNCTION(Reliable,Server)
	void SetAgilePoints(int32 AgilePointsSet);
	UFUNCTION(BlueprintCallable)
	int32 GetCascadePoints();
	UFUNCTION(Reliable,Server)
	void SetCascadePoints(int32 CascadePointsSet);
	UFUNCTION(BlueprintCallable)
	ETeam GetTeamFlagOwner();
	UFUNCTION(Reliable,Server)
	void SetTeamFlagOwner(ETeam ChosenTeamSet);

private:

	UPROPERTY(ReplicatedUsing=SetGameplayTime)
	float GameplayTime;
	
	UPROPERTY(ReplicatedUsing=SetLifeTerritory1)
	float LifeTerritory1;
	UPROPERTY(ReplicatedUsing=SetOwnerTerritory1)
	ETeam OwnerTerritory1;
	UPROPERTY(ReplicatedUsing=SetBlockTerritory1)
	bool BlockTerritory1;
	
	UPROPERTY(ReplicatedUsing=SetLifeTerritory2)
	float LifeTerritory2;
	UPROPERTY(ReplicatedUsing=SetOwnerTerritory2)
	ETeam OwnerTerritory2;
	UPROPERTY(ReplicatedUsing=SetBlockTerritory2)
	bool BlockTerritory2;
	
	UPROPERTY(ReplicatedUsing=SetLifeTerritory3)
	float LifeTerritory3;
	UPROPERTY(ReplicatedUsing=SetOwnerTerritory3)
	ETeam OwnerTerritory3;
	UPROPERTY(ReplicatedUsing=SetBlockTerritory3)
	bool BlockTerritory3;
	
	UPROPERTY(ReplicatedUsing=SetLifeTerritory4)
	float LifeTerritory4;
	UPROPERTY(ReplicatedUsing=SetOwnerTerritory4)
	ETeam OwnerTerritory4;
	UPROPERTY(ReplicatedUsing=SetBlockTerritory4)
	bool BlockTerritory4;
	
	UPROPERTY(ReplicatedUsing=SetWinnerTeam)
	ETeam WinnerTeam = ETeam::NoJob;

	UPROPERTY(ReplicatedUsing=SetAgilePoints)
	int32 AgilePoints;
	
	UPROPERTY(ReplicatedUsing=SetCascadePoints)
	int32 CascadePoints;

	UPROPERTY(ReplicatedUsing=SetTeamFlagOwner)
	ETeam TeamFlagOwner = ETeam::NoJob;


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
