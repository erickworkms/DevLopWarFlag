
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "DetectAttackEnd.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API UDetectAttackEnd : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation) override;
};
