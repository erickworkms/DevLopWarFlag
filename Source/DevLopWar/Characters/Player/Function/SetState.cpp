
#include "DevLopWar/Characters/Enums/EnumList.h"
#include "DevLopWar/Characters/Player/Player_Base.h"
#include "GameFramework/CharacterMovementComponent.h"


void APlayer_Base::SetState()
{
	if (GetCharacterMovement()->MovementMode == MOVE_Falling)
	{
		CurrentState = StateTypes::Falling;
	}
	else if (GetCharacterMovement()->MovementMode == MOVE_Flying)
	{
		CurrentState = Flying;
	}
	else if (GetCharacterMovement()->MovementMode == MOVE_Walking)
	{
		CurrentState = Ontheground;
	}
	else
	{
		CurrentState = Ontheground;
	}
}
