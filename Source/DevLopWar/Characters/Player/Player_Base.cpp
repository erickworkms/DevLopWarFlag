#include "Player_Base.h"
#include "Net/UnrealNetwork.h"
#include "Components/SkeletalMeshComponent.h"

APlayer_Base::APlayer_Base()
{
	CreateCharacterConfig();
	CreateCameraConfig();
}

void APlayer_Base::BeginPlay()
{
	Super::BeginPlay();
	SetDefaultValues();
	CheckChosenCharacter();

}

void APlayer_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetState();
	SetDefaultValuesVel(DeltaTime);
	if (Life <= 0)
	{
		DisableFlag();
	}
}

// Called to bind functionality to input
void APlayer_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayer_Base::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveSide"), this, &APlayer_Base::MoveSide);

	PlayerInputComponent->BindAxis(TEXT("CheckCameraForward"), this, &APlayer_Base::CheckCameraForward);
	PlayerInputComponent->BindAxis(TEXT("CheckCameraSide"), this, &APlayer_Base::CheckCameraSide);

	PlayerInputComponent->BindAction(TEXT("Pulo"), IE_Pressed, this, &APlayer_Base::CheckJump_Pressed);
	PlayerInputComponent->BindAction(TEXT("Pulo"), IE_Released, this, &APlayer_Base::CheckJump_Released);

	PlayerInputComponent->
		BindAction(TEXT("Atirar"), IE_Pressed, this, &APlayer_Base::Fire_Pressed);
	PlayerInputComponent->BindAction(TEXT("Atirar"), IE_Released, this, &APlayer_Base::Fire_Released);

	PlayerInputComponent->BindAction(TEXT("EnableTarget"), IE_Pressed, this, &APlayer_Base::EnableTarget_Pressed);
	PlayerInputComponent->BindAction(TEXT("EnableTarget"), IE_Released, this, &APlayer_Base::EnableTarget_Released);

	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this,
	                                 &APlayer_Base::Interact_Pressed);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Released, this,
	                                 &APlayer_Base::Interact_Released);
}

void APlayer_Base::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	CheckChosenCharacter();
}

void APlayer_Base::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(APlayer_Base, Life);
	DOREPLIFETIME(APlayer_Base, Speed);
	DOREPLIFETIME(APlayer_Base, BodyAngle);
	DOREPLIFETIME(APlayer_Base, CameraAngleX);
	DOREPLIFETIME(APlayer_Base, CameraAngleY);
	DOREPLIFETIME(APlayer_Base, FireSpeed);
	DOREPLIFETIME(APlayer_Base, GunHeatStats);
	DOREPLIFETIME(APlayer_Base, DamageAmount);
	DOREPLIFETIME(APlayer_Base, FireSpeed);
	DOREPLIFETIME(APlayer_Base, MaxSpeed);
	DOREPLIFETIME(APlayer_Base, VelTimerAnimation);
	DOREPLIFETIME(APlayer_Base, TargetRotation);

	DOREPLIFETIME(APlayer_Base, CanTarget);
	DOREPLIFETIME(APlayer_Base, BlockTimer);
	DOREPLIFETIME(APlayer_Base, IsCharacterMoving);
	DOREPLIFETIME(APlayer_Base, AllowFire);
	DOREPLIFETIME(APlayer_Base, HeatedGun);
	DOREPLIFETIME(APlayer_Base, HasFlag);
	
	DOREPLIFETIME(APlayer_Base, CurrentState);
	DOREPLIFETIME(APlayer_Base, Action);
	DOREPLIFETIME(APlayer_Base, NPC_Character);
	DOREPLIFETIME(APlayer_Base, Weapon);
	DOREPLIFETIME(APlayer_Base, LocalCameraReference);
	DOREPLIFETIME(APlayer_Base, ProjectileTimer);
	DOREPLIFETIME(APlayer_Base, MainCamera);
	DOREPLIFETIME(APlayer_Base, SpringArm);
	DOREPLIFETIME(APlayer_Base, LocalSocketWeapon);
	DOREPLIFETIME(APlayer_Base, RotationSocketWeapon);
	
	DOREPLIFETIME(APlayer_Base, Junior_Anim);
	DOREPLIFETIME(APlayer_Base, Tecnical_Anim);
	DOREPLIFETIME(APlayer_Base, Senior_Anim);
	DOREPLIFETIME(APlayer_Base, Boss_Anim);
	
	DOREPLIFETIME(APlayer_Base, MeshesPlayer);
	DOREPLIFETIME(APlayer_Base, AnimationPlayer);
	DOREPLIFETIME(APlayer_Base, WeaponPath);
	DOREPLIFETIME(APlayer_Base, Flag);
	DOREPLIFETIME(APlayer_Base, MeshesFlag);
}
