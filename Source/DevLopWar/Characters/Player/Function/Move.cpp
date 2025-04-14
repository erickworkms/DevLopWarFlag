

#include "Components/SkeletalMeshComponent.h"
#include "DevLopWar/Characters/Player/Player_Base.h"
#include "Kismet/KismetMathLibrary.h"

void APlayer_Base::MoveForward(float Value)
{
	if (Action != FallOntheFloor && Action != Dead)
	{
		FVector Frente = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

		FVector Costas = UKismetMathLibrary::GetRightVector
			(FRotator(0, GetControlRotation().Yaw, 0));
		AddMovementInput(Frente, Value);
	}
}

void APlayer_Base::MoveSide(float Value)
{
	if (Action != FallOntheFloor && Action != Dead)
	{
		FVector Lado = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);

		AddMovementInput(Lado, Value);
	}
}