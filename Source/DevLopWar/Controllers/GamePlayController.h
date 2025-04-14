

#pragma once

#include "CoreMinimal.h"
#include "DevLopWar/Characters/Enums/EnumList.h"
#include "DevLopWar/Characters/Player/Player_Base.h"

#include "DevLopWar/Structs/Struct.h"
#include "DevLopWar/Huds/BaseHudGameplay.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayController.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API AGamePlayController : public APlayerController
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,Reliable,Server)
	void CreateCharacter();

	UFUNCTION(BlueprintCallable,Reliable,Server)
	void ChooseCharacter(NPC_CharacterType NPC_Character);

	UFUNCTION(BlueprintCallable,Reliable,Client)
	void ChooseClientCharacter(NPC_CharacterType NPC_Character);

	UPROPERTY(BlueprintReadWrite,Replicated)
	APlayer_Base* BaseCharacter;

	UPROPERTY(BlueprintReadWrite,Replicated)
	ABaseHudGameplay* Hud;

	UFUNCTION(Reliable,Client)
	void ActiveEndGameHud();

	UFUNCTION(Reliable,Client)
	void CheckInstanceData(FPlayerGameplayInformation GameplayInformation);

	UFUNCTION(Reliable,Client)
	void AddDataInstanceServer();
	
	FPlayerGameplayInformation CreatePlayerInformation();
	
	int ReturnPlayerIndex();
//
	UFUNCTION(Reliable,NetMulticast)
	void RevivePlayer();
	
	UFUNCTION(BlueprintCallable,Reliable,Server)
	void AddPlayerListServer(AGamePlayController* Controller,FPlayerGameplayInformation GameplayInformation,int PlayerIndex);
protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
