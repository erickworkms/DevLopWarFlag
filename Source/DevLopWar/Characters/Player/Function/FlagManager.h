

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlagManager.generated.h"

UCLASS()
class DEVLOPWAR_API AFlagManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AFlagManager();

	UPROPERTY()
	UStaticMeshComponent* NPCLocalReference;

	UPROPERTY(EditAnywhere,Replicated,meta = (AllowPrivateAccess = "true"))
	AActor* FlagObject;

	UPROPERTY(Replicated,meta = (AllowPrivateAccess = "true"))
	FVector StartLocation;
	
	UFUNCTION(Reliable,Server)
	void SetFlagLocation(FVector NewLocation);

	UFUNCTION(Reliable,Server)
	void RespawnFlag();

	FTimerHandle Timer;
	
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
