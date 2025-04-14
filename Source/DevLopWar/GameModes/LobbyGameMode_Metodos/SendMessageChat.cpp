

#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/Controllers/LobbyController.h"
#include "DevLopWar/GameModes/LobbyGameMode.h"

void ALobbyGameMode::SendMessageChat_Implementation(const FString& mensagem)
{
	UWorld* World = GetWorld();
	check(World);
	if (GetLocalRole() == ROLE_Authority)
	{
		for (int i = 0; i < PlayerRoom.Num();i++)
		{
			if (IsValid(PlayerRoom[i]))
			{
				ALobbyController* PlayerState = Cast<ALobbyController>(PlayerRoom[i]);
				if (IsValid(PlayerState))
				{
					PlayerState->SendMessageClient(PlayerRoom[i]->GetName(),mensagem);
				}
			}
		}
	}
}
