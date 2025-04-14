

#pragma once

#include "CoreMinimal.h"
#include "FlagManager.h"
#include "Components/BoxComponent.h"

#include "DevLopWar/Structs/Struct.h"
#include "GameFramework/Actor.h"
#include "PortalObject.generated.h"

UCLASS()
class DEVLOPWAR_API APortalObject : public AActor
{
	GENERATED_BODY()
	
public:	
	APortalObject();

	UPROPERTY(Replicated,EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* NPCLocalReference;

	UPROPERTY(Replicated,EditAnywhere,Replicated,meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Collision;

	UPROPERTY(EditAnywhere,Replicated,meta = (AllowPrivateAccess = "true"))
	AFlagManager* FlagManager;

	UFUNCTION()
	void ShowPortal(ETeam team);
	
	UFUNCTION()
	void HidePortal();

	UFUNCTION(BlueprintImplementableEvent)
	void SetPortalMaterial(ETeam team);
	
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:

	UFUNCTION(Reliable,Server)
	void StartCollision(UPrimitiveComponent* OverlappedComp, AActor* DetectedCharacter,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult);
	
};
