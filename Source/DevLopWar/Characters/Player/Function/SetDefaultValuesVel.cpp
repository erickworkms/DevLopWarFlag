
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "DevLopWar/Characters/Player/Player_Base.h"
#include "GameFramework/CharacterMovementComponent.h"


void APlayer_Base::SetDefaultValuesVel_Implementation(float Value)
{
	if (CanTarget == true)
	{
		MaxSpeed = 300;
		GetCapsuleComponent()->SetRelativeRotation(FRotator(0, TargetRotation,
													0));
		if (AllowFire == true && HeatedGun)
		{
			GunHeatStats += 1;
			if (GunHeatStats >= 99)
			{
				HeatedGun = false;
			}
		}
	}
	else
	{
		if (HeatedGun)
		{
			GunHeatStats += 1;
			if (GunHeatStats >= 99)
			{
				HeatedGun = false;
			}
		}
		MaxSpeed = 600;
	}
	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
	IsCharacterMoving = (GetCapsuleComponent()->GetComponentVelocity().GetAbs().X
		+ GetCapsuleComponent()->GetComponentVelocity().GetAbs().Y) > 0;
	Speed = GetCapsuleComponent()->GetComponentVelocity().GetAbs().X
		+ GetCapsuleComponent()->GetComponentVelocity().GetAbs().Y;
	Speed = FMath::FInterpTo(GetCapsuleComponent()->GetComponentVelocity().Size(),
	                              Speed, Value, 10.f);

	CheckZAngle = FMath::FInterpTo(CheckZAngle,
	                                        GetCharacterMovement()->GetLastUpdateVelocity().Z, Value, 10.f);
	if (Life <= 0.0f)
	{
		Action = Dead;
	}
}