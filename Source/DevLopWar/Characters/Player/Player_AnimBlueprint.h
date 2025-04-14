#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DevLopWar/Characters/Enums/EnumList.h"
#include "Player_AnimBlueprint.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API UPlayer_AnimBlueprint : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayer_AnimBlueprint();
	
	FVector LocalWeapon;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	float Life;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	float Speed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	float BodyAngle = 0.f;;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	float CameraAngleX = 0.f;;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	float CameraAngleY = 0.f;;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	float Direction = 0.f;;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	float VelTimerAnimation = 0.f;;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	bool Target;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	TEnumAsByte<StateTypes> CurrentState = Ontheground;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	TEnumAsByte<ActionType> Action = NoCharacterData;
	
	//Lista de funções
	UFUNCTION(CallInEditor, BlueprintCallable, Category=Animation)
	void CheckDirection(APawn* BaseCharacter);
	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds);

private:
	UPROPERTY()
	APawn* Character = NULL;
};
