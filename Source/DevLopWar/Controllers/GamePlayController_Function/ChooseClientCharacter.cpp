

#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopWar/Controllers/GamePlayController.h"
#include "DevLopWar/Characters/Player/Player_Base.h"

void AGamePlayController::ChooseCharacter_Implementation(NPC_CharacterType NPC_Character)
{
	if (IsValid(GetPawn()) && HasAuthority())
	{
		BaseCharacter = Cast<APlayer_Base>(GetPawn());
		if (IsValid(BaseCharacter))
		{
			bShowMouseCursor = false;
			BaseCharacter->NPC_Character = NPC_Character;
			BaseCharacter->CheckChosenCharacter();
			ChooseClientCharacter(NPC_Character);
		}
	}
}

void AGamePlayController::ChooseClientCharacter_Implementation(NPC_CharacterType NPC_Character)
{
	if (IsValid(GetPawn()))
	{
		BaseCharacter = Cast<APlayer_Base>(GetPawn());
		if (IsValid(BaseCharacter))
		{
			bShowMouseCursor = false;
			BaseCharacter->NPC_Character = NPC_Character;
			BaseCharacter->CheckChosenCharacter();
		}
	}
}