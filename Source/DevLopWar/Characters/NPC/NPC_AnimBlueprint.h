
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DevLopWar/Characters/Enums/EnumList.h"
#include "NPC_AnimBlueprint.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API UNPC_AnimBlueprint : public UAnimInstance
{
	GENERATED_BODY()

public:
	UNPC_AnimBlueprint();
	
	FVector LocalWeapon;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	float Life;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	float Speed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	TEnumAsByte<StateTypes> CurrentState = Ontheground;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	TEnumAsByte<ActionType> Action = NoCharacterData;
	
	//Lista de funções	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds);

private:
	UPROPERTY()
	APawn* Character;
};
