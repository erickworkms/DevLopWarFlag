


#include "NPC_AnimBlueprint.h"
#include "NPC_Base.h"

UNPC_AnimBlueprint::UNPC_AnimBlueprint()
{
	Speed = 0.f;
}

void UNPC_AnimBlueprint::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = TryGetPawnOwner();
}

void UNPC_AnimBlueprint::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Character)
	{
		return;
	}
	if (Character->IsA(ANPC_Base::StaticClass()))
	{
		ANPC_Base* CharacterReference = Cast<ANPC_Base>(Character);
		
		if (CharacterReference)
		{
			Life = CharacterReference->Life;
			Speed = CharacterReference->Speed;
			CurrentState = CharacterReference->CurrentState;
			Action = CharacterReference->Action;
		}
	}
}
