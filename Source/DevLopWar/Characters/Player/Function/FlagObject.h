

#pragma once

#include "CoreMinimal.h"
#include "FlagManager.h"
#include "Components/BoxComponent.h"
#include "DevLopWar/Characters/Player/Player_Base.h"
#include "DevLopWar/PlayerStates/DevOpPlayerState.h"
#include "DevLopWar/Structs/Struct.h"
#include "GameFramework/Actor.h"
#include "FlagObject.generated.h"

UCLASS()
class DEVLOPWAR_API AFlagObject : public AActor
{
	GENERATED_BODY()
	
public:	
	AFlagObject();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* NPCLocalReference;

	UPROPERTY(Replicated,meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Collision;

	UPROPERTY(EditAnywhere,Replicated,meta = (AllowPrivateAccess = "true"))
	AFlagManager* FlagManager;

	UFUNCTION(Reliable,Server)
	void ChangeFlagTeamOwner(ETeam Team);

	FTimerHandle Timer;
	
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:

	UFUNCTION()
	void StartCollision(UPrimitiveComponent* OverlappedComp, AActor* DetectedCharacter,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult)
	{
		APlayer_Base* Character = Cast<APlayer_Base>(DetectedCharacter);
		
		if (IsValid(Character))
		{
			if (Character->Life > 0)
			{
				ADevOpPlayerState* PlayerStateFound = Cast<ADevOpPlayerState>(Character->GetPlayerState());
				Character->HasFlag = true;
				Character->EnableFlag();
				ChangeFlagTeamOwner(PlayerStateFound->GetChosenTeam());
			}
		}
	}
};
