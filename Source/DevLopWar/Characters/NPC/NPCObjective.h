

#pragma once

#include "CoreMinimal.h"
#include "DevLopWar/Characters/Player/Function/PortalObject.h"
#include "DevLopWar/Structs/Struct.h"
#include "GameFramework/Actor.h"
#include "NPCObjective.generated.h"

UCLASS()
class DEVLOPWAR_API AObjectiveNPC : public AActor
{
	GENERATED_BODY()
	
public:	
	AObjectiveNPC();

	UPROPERTY()
	UStaticMeshComponent* NPCLocalReference;

	UPROPERTY(Replicated,BlueprintReadWrite)
	float Life = 500;

	UPROPERTY(Replicated)
	ETeam TeamTerritory = ETeam::NoJob;

	UPROPERTY(Replicated,BlueprintReadWrite,EditAnywhere)
	int TerritoryIndex = 1;

	UPROPERTY(Replicated,BlueprintReadWrite)
	bool IsBlocked = false;

	UFUNCTION(Reliable,Server)
	void GameTimer();

	UPROPERTY(EditAnywhere,Replicated,BlueprintReadWrite)
	APortalObject* Portal;
	
	FTimerHandle Timer;
	
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
