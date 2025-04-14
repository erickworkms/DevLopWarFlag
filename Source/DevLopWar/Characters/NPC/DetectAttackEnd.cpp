

#include "DetectAttackEnd.h"
#include "NPC_Base.h"

void UDetectAttackEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	ANPC_Base* NPC = Cast<ANPC_Base>(MeshComp->GetOwner());
	if (IsValid(NPC))
	{
		NPC->CanMove = true;
		NPC->Action = NoCharacterData;
	}
}
