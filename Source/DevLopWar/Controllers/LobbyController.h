

#pragma once

#include "CoreMinimal.h"
#include "DevLopWar/Huds/BaseHudMainMenu.h"
#include "GameFramework/PlayerController.h"
#include "LobbyController.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API ALobbyController : public APlayerController
{
	GENERATED_BODY()

public:
	ALobbyController();
	UFUNCTION(BlueprintCallable,Reliable,Server)
	void SendMessageServer(const FString& name,const FString& Message);

	UFUNCTION(Reliable,Client)
	void SendMessageClient(const FString& name,const FString& Message);
	
	UFUNCTION(Reliable,Client)
	void CheckEntryLogin(const TArray<FString>& PlayerRoomName);

	UFUNCTION(Reliable,Client)
	void AddDataInstance(int32 PlayerIndex);
	
	UPROPERTY(Replicated,BlueprintReadWrite)
	ABaseHudMainMenu* HudChat;

	UPROPERTY(Replicated)
	FString User = "Server";
	UFUNCTION(BlueprintCallable)
	FString GetUser() const;
	UFUNCTION(Reliable,Server,BlueprintCallable)
	void SetUser(const FString& UserSet);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

};
