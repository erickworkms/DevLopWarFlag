

#include "DevLopWar/Characters/Enums/EnumList.h"
#include "DevLopWar/Characters/Player/Player_Base.h"

void APlayer_Base::CheckChosenCharacter()
{
	if(MeshesPlayer.Num() >= 4 && AnimationPlayer.Num() >=4)
	{
		switch (NPC_Character)
		{
		case Junior:
			CheckCharacterMesh(0);
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(Junior_Anim);
			break;
		case Tecnical:
			CheckCharacterMesh(1);
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(Tecnical_Anim);
			break;
		case Senior:
			CheckCharacterMesh(2);
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(Senior_Anim);
			break;
		case Boss:
			CheckCharacterMesh(3);
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(Boss_Anim);
			break;
		default:
			CheckCharacterMesh(0);
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(Junior_Anim);
			break;
		}
	}
}
void APlayer_Base::LoadCharacterAssets()
{
	
}