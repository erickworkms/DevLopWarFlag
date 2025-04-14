

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHudGameplay.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API ABaseHudGameplay : public AHUD
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void EnableWinnerScreen();
	
	UPROPERTY(BlueprintReadWrite,Replicated)
	ABaseHudGameplay* HudGameplay;
};
