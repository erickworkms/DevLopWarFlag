

#include "DevLopWar/Characters/Enums/EnumList.h"
#include "DevLopWar/Characters/Player/Player_Base.h"

void APlayer_Base::CheckJump_Pressed()
{
	if (CurrentState == Ontheground)
	{
		Jump();
		Action = JumpAction;
	}
}

void APlayer_Base::CheckJump_Released()
{
}