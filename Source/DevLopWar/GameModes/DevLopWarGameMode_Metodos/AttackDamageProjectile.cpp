
#include "DevLopWar/Characters/NPC/NPC_Base.h"
#include "DevLopWar/GameModes/DevLopWarGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

void ADevLopWarGameMode::AttackDamageProjectile_Implementation(AActor* OwnerProjetil, AActor* DetectedEnemy,
                                                           AActor* Projetil)
{
	APlayer_Base* Player_Detectado = Cast<APlayer_Base>(DetectedEnemy);
	APlayer_Base* Enemy = Cast<APlayer_Base>(OwnerProjetil);
	AObjectiveNPC* Territory = Cast<AObjectiveNPC>(DetectedEnemy);
	ANPC_Base* NPC_Detected = Cast<ANPC_Base>(DetectedEnemy);

	int OwnerIndex = 0;
	int AlvoIndex = 0;

	if (IsValid(Player_Detectado))
	{
		if (Player_Detectado->Life > 0)
		{
			for (int i = 0; i < PlayerRoom.Num(); i++)
			{
				if (IsValid(PlayerRoom[i]))
				{
					if (PlayerRoom[i] == Player_Detectado->GetController())
					{
						AlvoIndex = i;
					}
					else if (PlayerRoom[i] == Enemy->GetController())
					{
						OwnerIndex = i;
					}
				}
			}
			Player_Detectado->Life -= Enemy->DamageAmount;

			if (Player_Detectado->Life <= 0)
			{
				AGamePlayController* PlayerControle = Cast<AGamePlayController>(PlayerRoom[AlvoIndex]);
				ChangeNumDeadPlayers(OwnerIndex);
				ChangeNumDeaths(AlvoIndex);
				GetWorldTimerManager().SetTimer(ReviverTimer[AlvoIndex], PlayerControle, &AGamePlayController::RevivePlayer, 5, false);

				if (Player_Detectado->HasFlag)
				{
					Player_Detectado->HasFlag = false;
					Player_Detectado->DisableFlag();

					TArray<AActor*> ManagerFound;
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFlagManager::StaticClass(), ManagerFound);
				
					for (AActor* Actor : ManagerFound)
					{
						AFlagManager* Manager = Cast<AFlagManager>(Actor);
						if (Manager)
						{
							//Manager->RespawnFlag();
							Manager->SetFlagLocation(Player_Detectado->GetActorLocation());
						}
					}
				}
			}
		}
		Projetil->Destroy();
	}


	if (IsValid(NPC_Detected))
	{
		if (NPC_Detected->Life > 0)
		{
			if (NPC_Detected->EnemyFound == NULL)
			{
				NPC_Detected->EnemyFound = OwnerProjetil;
				NPC_Detected->AI_Behavior = AI_StateType::Follow_NPC;
			}
			for (int i = 0; i < PlayerRoom.Num(); i++)
			{
				if (IsValid(PlayerRoom[i]))
				{
					if (PlayerRoom[i] == Enemy->GetController())
					{
						OwnerIndex = i;
					}
				}
			}
			NPC_Detected->Life -= Enemy->DamageAmount;
			if (NPC_Detected->Life <= 0)
			{
				NPC_Detected->DeleteCounterNPC();
				ChangeNumDeadZombies(OwnerIndex);
			}
		}
		Projetil->Destroy();
	}
	else if (IsValid(Territory))
	{
		for (int i = 0; i < PlayerRoom.Num(); i++)
		{
			if (IsValid(PlayerRoom[i]))
			{
				if (PlayerRoom[i] == Enemy->GetController())
				{
					OwnerIndex = i;
				}
			}
		}
		if (Territory->Life > 0 && Territory->IsBlocked == false && !GameStateServer->GetCheckTakenTerritory(Territory->TerritoryIndex,GameplayInformation[OwnerIndex].ChosenTeam))
		{
			Territory->Life -= Enemy->DamageAmount;
			
			switch (Territory->TerritoryIndex)
			{
			case 1:
				GameStateServer->SetLifeTerritory1(Territory->Life);
				break;
			case 2:
				GameStateServer->SetLifeTerritory2(Territory->Life);
				break;
			case 3:
				GameStateServer->SetLifeTerritory3(Territory->Life);
				break;
			case 4:
				GameStateServer->SetLifeTerritory4(Territory->Life);
				break;
			default:
				break;
			}
			if (Territory->Life <= 0)
			{
				Territory->Life = 100;
				switch (Territory->TerritoryIndex)
				{
				case 1:
					GameStateServer->SetOwnerTerritory1(GameplayInformation[OwnerIndex].ChosenTeam);
					GameStateServer->SetLifeTerritory1(Territory->Life);
					break;
				case 2:
					GameStateServer->SetOwnerTerritory2(GameplayInformation[OwnerIndex].ChosenTeam);
					GameStateServer->SetLifeTerritory2(Territory->Life);
					break;
				case 3:
					GameStateServer->SetOwnerTerritory3(GameplayInformation[OwnerIndex].ChosenTeam);
					GameStateServer->SetLifeTerritory3(Territory->Life);
					break;
				case 4:
					GameStateServer->SetOwnerTerritory4(GameplayInformation[OwnerIndex].ChosenTeam);
					GameStateServer->SetLifeTerritory4(Territory->Life);
					break;
				default:
					break;
				}
				Territory->IsBlocked = true;
				Territory->Portal->ShowPortal(GameStateServer->GetTeamFlagOwner());
				EnableObjectivePoints(Territory->TerritoryIndex,Territory->IsBlocked);
				GetWorldTimerManager().SetTimer(Territory->Timer, Territory, &AObjectiveNPC::GameTimer, 5, false);
			}
		}
		Projetil->Destroy();
	}
	else if (DetectedEnemy != OwnerProjetil)
	{
		Projetil->Destroy();
	}
}
