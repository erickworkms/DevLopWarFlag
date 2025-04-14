

#pragma once

#include "CoreMinimal.h"
#include "NPCObjective.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "EngineUtils.h"
#include "Components/StaticMeshComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "DevLopWar/Characters/Player/Player_Base.h"
#include "DevLopWar/Controllers/GamePlayController.h"
#include "DevLopWar/GameModes/DevLopWarGameMode.h"
#include "NPC_Base.generated.h"

UCLASS()
class DEVLOPWAR_API ANPC_Base : public ACharacter
{
	GENERATED_BODY()

public:
	ANPC_Base();

	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float Life = 1;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float Speed;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float MaxSpeed = 500;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float CombatDistance = 150;

	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	bool CanMove = true;
	
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	TEnumAsByte<StateTypes> CurrentState = Ontheground;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	TEnumAsByte<ActionType> Action = NoCharacterData;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	TEnumAsByte<AI_StateType> AI_Behavior;
	UPROPERTY(Replicated,meta = (AllowPrivateAccess = "true"))
	UBoxComponent* AttackDamage;
	UPROPERTY(Replicated,EditAnywhere,meta = (AllowPrivateAccess = "true"))
	AObjectiveNPC* ObjectivePatrolLocation;
	
	UPROPERTY(Replicated,meta = (AllowPrivateAccess = "true"))
	AActor* EnemyFound;
	
	UPROPERTY()
	UBlackboardComponent* AIVariables_BlackBoard;
	UPROPERTY()
	AAIController* NPCController;

	UPROPERTY(Replicated,meta = (AllowPrivateAccess = "true"))
	FString MeshPlayer;
	UPROPERTY(Replicated,meta = (AllowPrivateAccess = "true"))
	FString AnimationPlayer;
	
	void ManageAIChosenEnemy();
protected:
	
	virtual void BeginPlay() override;

	UFUNCTION(Reliable,Server)
	void SetDefaultValuesVel(float deltatime);
	
	void CheckDefaultValues();

	UFUNCTION(Reliable,Server)
	void CheckLife();
	
	UFUNCTION(Reliable,Server)
	void SetState();

	UFUNCTION(Reliable,Server)
	void CheckPatrolLocation();
	
	UFUNCTION(Reliable,Server)
	void MoveCharacterPatrol(FVector PatrolLocation);
	
	UFUNCTION(Reliable,Server)
	void CheckBehaviorFunction();
	
	UFUNCTION(Reliable,Server)
	void ManageAICharacterVision();
public:
	UFUNCTION(Reliable,Server)
	void DeleteCounterNPC();

	UFUNCTION(Reliable,Server)
	void DeleteNPC();

	UFUNCTION(Reliable,Server)
	void ResetNPC();

	UFUNCTION(Reliable,Server)
	void StartNPC();

	UFUNCTION(Reliable,NetMulticast)
	void InitializeCharacterAttachment();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void StartDamageCollision(UPrimitiveComponent* OverlappedComp, AActor* DetectedEnemy,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult)
	{
		if(Action == Attack && DetectedEnemy != this)
		{
			AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
			ADevLopWarGameMode* DevGameMode = Cast<ADevLopWarGameMode>(GameMode);
			APlayer_Base* DetectedPlayer = Cast<APlayer_Base>(DetectedEnemy);
			AObjectiveNPC* Territory_Detected = Cast<AObjectiveNPC>(DetectedEnemy);
			
			if (IsValid(DetectedPlayer))
			{
				if (DetectedPlayer->Life > 0)
				{				
					DetectedPlayer->Life -= 10;
					if (DetectedPlayer->Life <= 0)
					{
						AGamePlayController* DetectedController = Cast<AGamePlayController>(DetectedPlayer->GetController());
						if (IsValid(DetectedController))
						{
							FTimerHandle Timer;
							GetWorldTimerManager().SetTimer(Timer, DetectedController, &AGamePlayController::RevivePlayer, 5, false);
							
							if (IsValid(GameMode))
							{
								if (IsValid(DevGameMode))
								{
									int PlayerNumber = DevGameMode->ReturnPlayerIndex(DetectedController);
									if (PlayerNumber != 100)
									{
										DevGameMode->ChangeNumDeaths(PlayerNumber);
									}
								}
							}
						}
					}
				}
			}else if (IsValid(Territory_Detected) && IsValid(DevGameMode))
			{
				DevGameMode->UpdateTerritoryNPCDamage(Territory_Detected);
				if (Territory_Detected->Life <= 0)
				{
					TArray<AObjectiveNPC*> NPCList;
					for (TActorIterator<AObjectiveNPC> It(GetWorld()); It; ++It)
					{
						if (It->TeamTerritory != ETeam::Clients)
						{
							NPCList.Add(*It);
						}
					}
					if (NPCList.Num() > 0)
					{
						ObjectivePatrolLocation = NPCList[FMath::RandRange(0, NPCList.Num() - 1)];
						MoveCharacterPatrol(ObjectivePatrolLocation->GetActorLocation());
					}
				}
				
			}
		}
	}

	UFUNCTION()
	void EndDamageCollision(UPrimitiveComponent* OverlappedComp, AActor* DetectedEnemy,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
	{
		
	}
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};


