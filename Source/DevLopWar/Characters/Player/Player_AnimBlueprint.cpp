
#include "Player_AnimBlueprint.h"
#include "Player_Base.h"
#include "GameFramework/CharacterMovementComponent.h"


void UPlayer_AnimBlueprint::CheckDirection(APawn* BaseCharacter)
{
	APlayer_Base* CharacterReference = Cast<APlayer_Base>(BaseCharacter);
	Direction = CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());

	if (Speed > 500)
	{
		VelTimerAnimation = FMath::Clamp(Speed /
									   FMath::Clamp(BaseCharacter->GetMovementComponent()->GetMaxSpeed(),
													0.0f, CharacterReference->MaxSpeed), 1.f,5.f);
	}
	else
	{
		VelTimerAnimation = 1;
	}
}

UPlayer_AnimBlueprint::UPlayer_AnimBlueprint()
{
	Life = 100.f;
	Speed = 0.f;
	Target = .0f;
}

void UPlayer_AnimBlueprint::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = TryGetPawnOwner();
}

void UPlayer_AnimBlueprint::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Character)
	{
		return;
	}
	if (Character->IsA(APlayer_Base::StaticClass()))
	{
		APlayer_Base* CharacterReference = Cast<APlayer_Base>(Character);
		
		if (CharacterReference)
		{
			CheckDirection(CharacterReference);

			Life = CharacterReference->Life;
			Speed = CharacterReference->Speed;
			BodyAngle = CharacterReference->BodyAngle;
			CameraAngleX = CharacterReference->CameraAngleX;
			CameraAngleY = CharacterReference->CameraAngleY;
			Direction = CharacterReference->Direction;
			VelTimerAnimation = CharacterReference->VelTimerAnimation;
	
			Target = CharacterReference->CanTarget;

			CurrentState = CharacterReference->CurrentState;
			Action = CharacterReference->Action;
		}
	}
}


