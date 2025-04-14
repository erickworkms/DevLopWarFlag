
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DevLopWar/Characters/Player/Player_Base.h"


void APlayer_Base::CheckCameraForward(float Value)
{
	CheckCameraForwardServer(Value);
	float CameraRotation = MainCamera->GetSocketRotation("none").Pitch * -1;

	if (Value != 0)
	{
		if (CanTarget)
		{
			CameraAngleY = CameraRotation * -1;

			if (CameraRotation < 49 && Value > 0)
			{
				AddControllerPitchInput(Value);
			}
			else if (CameraRotation > -45 && Value < 0)
			{
				AddControllerPitchInput(Value);
			}
		}
		else if (!CanTarget)
		{
			CameraAngleY = 0.0f;
			
			if (CameraRotation >= 49 && CameraRotation <= -15)
			{
				AddControllerPitchInput(Value);
			}
			else if (CameraRotation < 49 && Value > 0)
			{
				AddControllerPitchInput(Value);
			}
			else if (CameraRotation > -15 && Value < 0)
			{
				AddControllerPitchInput(Value);
			}
		}
	}
}

void APlayer_Base::CheckCameraSide(float Value)
{
	CheckCameraSideServer(Value);
	FVector Target = LocalCameraReference->GetComponentToWorld().GetLocation();

	if (Value != 0)
	{
		if (CanTarget)
		{
			if (CameraAngleX < 200 && Value < 0)
			{
				CameraAngleX = FVector::DotProduct(GetActorRightVector(), Target - GetActorLocation());
				AddControllerYawInput(Value);
			}
			else if (CameraAngleX > -295 && Value > 0)
			{
				CameraAngleX = FVector::DotProduct(GetActorRightVector(), Target - GetActorLocation());
				AddControllerYawInput(Value);
			}
		}
		else if (!CanTarget)
		{
			
			AddControllerYawInput(Value);
		}
	}
}

void APlayer_Base::CheckCameraForwardServer_Implementation(float Value)
{
	float CameraRotation = MainCamera->GetSocketRotation("none").Pitch * -1;

	if (Value != 0)
	{
		if (CanTarget)
		{
			CameraAngleY = CameraRotation * -1;

			if (CameraRotation < 35 && Value > 0)
			{
				AddControllerPitchInput(Value);
			}
			else if (CameraRotation > -35 && Value < 0)
			{
				AddControllerPitchInput(Value);
			}
		}
		else if (!CanTarget)
		{
			CameraAngleY = 0.0f;
			
			if (CameraRotation >= 49 && CameraRotation <= -15)
			{
				AddControllerPitchInput(Value);
			}
			else if (CameraRotation < 49 && Value > 0)
			{
				AddControllerPitchInput(Value);
			}
			else if (CameraRotation > -15 && Value < 0)
			{
				AddControllerPitchInput(Value);
			}
		}
	}
}

void APlayer_Base::CheckCameraSideServer_Implementation(float Value)
{
	FVector Target = LocalCameraReference->GetComponentToWorld().GetLocation();

	if (Value != 0)
	{
		if (CanTarget)
		{
			if (CameraAngleX < 150 && Value < 0)
			{
				CameraAngleX = FVector::DotProduct(GetActorRightVector(), Target - GetActorLocation());
				AddControllerYawInput(Value);
			}
			else if (CameraAngleX > -250 && Value > 0)
			{
				CameraAngleX = FVector::DotProduct(GetActorRightVector(), Target - GetActorLocation());
				AddControllerYawInput(Value);
			}
		}
		else if (!CanTarget)
		{
			AddControllerYawInput(Value);
		}
	}
}

void APlayer_Base::CreateCameraConfig()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->MaxSwimSpeed = 1000.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArm->SetupAttachment(RootComponent);
	
	SpringArm->bUsePawnControlRotation = true;

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	MainCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	MainCamera->bUsePawnControlRotation = false;
	MainCamera->GetCollisionResponseToChannel(ECC_Camera);
	MainCamera->SetIsReplicated(true);

	SpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 400.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 20.0f;

	SpringArm->bDoCollisionTest = false;
	SpringArm->ProbeSize = 15;
	SpringArm->ProbeChannel = ECC_Camera;
	SpringArm->SetIsReplicated(true);

	LocalCameraReference = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraReference"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Reference(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (Reference.Succeeded())
	{
		LocalCameraReference->SetStaticMesh(Reference.Object);
		LocalCameraReference->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
		LocalCameraReference->SetIsReplicated(true);
	}
	AutoPossessPlayer = EAutoReceiveInput::Disabled;
}