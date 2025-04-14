

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnNPC.generated.h"

UCLASS()
class DEVLOPWAR_API ASpawnNPC : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnNPC();
	
	UPROPERTY()
	UStaticMeshComponent* NPCLocalReference;
protected:
	FTimerHandle Timer;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Reliable,Server)
	void CreateNPC();
};
