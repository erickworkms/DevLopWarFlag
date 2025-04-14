

#pragma once

#include "CoreMinimal.h"
#include "DevLopWar/Structs/Struct.h"
#include "GameFramework/HUD.h"
#include "BaseHudMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API ABaseHudMainMenu : public AHUD
{
	GENERATED_BODY()

	ABaseHudMainMenu();
public:
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnFindSessionsComplete(bool bWasSuccessful);
	
	UFUNCTION(BlueprintImplementableEvent)
	void RemovePlayer(APlayerController* PlayerController);
	
	UFUNCTION(BlueprintImplementableEvent)
	void SendMessageChat(const FString& Message);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void AddHudRooms(const TArray<FString>& PlayersNames);
};
