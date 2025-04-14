

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "DevLopWar/Characters/Player/Player_Base.h"
#include "GameFramework/CharacterMovementComponent.h"


void APlayer_Base::Fire_Pressed()
{
	if (AllowFire == true && HeatedGun == false)
	{
		AllowFire = false;
		CreateProjectile();
		GetWorldTimerManager().SetTimer(ProjectileTimer, this, &APlayer_Base::Allow_Fire, FireSpeed, false);
		GunHeatStats -= FireSpeed * 30;
		if (GunHeatStats <= 0.0f)
		{
			HeatedGun = true;
		}
	}
}

void APlayer_Base::Fire_Released()
{
	AllowFire = true;
}

void APlayer_Base::EnableTarget_Pressed()
{
	EnableTarget_PressedServer();
	if (!CanTarget)
	{
		FRotator CameraRotationStart = MainCamera->GetComponentRotation() - FRotator::ZeroRotator;
		TargetRotation = GetCamera()->GetComponentRotation().Yaw;
	
		CameraAngleX = 0;
		CameraAngleY = 0;

		GetController()->SetControlRotation(
				FRotator(0, CameraRotationStart.Yaw, 0)
			);
		
		GetCapsuleComponent()->SetRelativeRotation(FRotator(0,TargetRotation,0));
	
		SpringArm->TargetArmLength = 70.0f;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		SpringArm->SetRelativeLocationAndRotation(FVector(0, 0, 25), FRotator(0, 0, 0));
		MainCamera->SetRelativeLocationAndRotation(FVector(0, 50, 0), FRotator(0, 0, 0));
		LocalCameraReference->SetRelativeLocation(FVector(-320, 0, -30));
	}
	CanTarget = true;
}

void APlayer_Base::EnableTarget_Released()
{
	EnableTarget_ReleasedServer();
	if (CanTarget)
	{
		SpringArm->TargetArmLength = 400.0f;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		MainCamera->SetRelativeLocationAndRotation(FVector(0, 0, 0), FRotator(0, 0, 0));
		CameraAngleX = 0;
		CameraAngleY = 0;
		LocalCameraReference->SetRelativeLocation(FVector(0, 0, 0));
	}
	CanTarget = false;
}

void APlayer_Base::EnableTarget_PressedServer_Implementation()
{
	if (!CanTarget)
	{
		FRotator CameraRotationStart = MainCamera->GetComponentRotation() - FRotator::ZeroRotator;
		TargetRotation = GetCamera()->GetComponentRotation().Yaw;
		
		CameraAngleX = 0;
		CameraAngleY = 0;
		
		GetController()->SetControlRotation(
							FRotator(0, CameraRotationStart.Yaw, 0)
						);
		GetCapsuleComponent()->SetRelativeRotation(FRotator(0, TargetRotation,
															0));
	
		SpringArm->TargetArmLength = 70.0f;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		SpringArm->SetRelativeLocationAndRotation(FVector(0, 0, 25), FRotator(0, 0, 0));
		MainCamera->SetRelativeLocationAndRotation(FVector(0, 50, 0), FRotator(0, 0, 0));
		LocalCameraReference->SetRelativeLocation(FVector(-320, 0, -30));
	}
	CanTarget = true;
}

void APlayer_Base::EnableTarget_ReleasedServer_Implementation()
{
	if (CanTarget)
	{
		SpringArm->TargetArmLength = 400.0f;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		MainCamera->SetRelativeLocationAndRotation(FVector(0, 0, 0), FRotator(0, 0, 0));
		CameraAngleX = 0;
		CameraAngleY = 0;
		LocalCameraReference->SetRelativeLocation(FVector(0, 0, 0));
	}
	CanTarget = false;
}
