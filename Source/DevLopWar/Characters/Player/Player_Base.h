

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DevLopWar/Characters/Enums/EnumList.h"
#include "Player_Base.generated.h"

UCLASS()
class DEVLOPWAR_API APlayer_Base : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated,meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated,meta = (AllowPrivateAccess = "true"))
	UCameraComponent* MainCamera;
	UPROPERTY(Replicated,meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Weapon;
	UPROPERTY(Replicated,meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LocalCameraReference;
	UPROPERTY(Replicated,meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Flag;

public:

	APlayer_Base();
	
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	FTimerHandle ProjectileTimer;

	UPROPERTY(Replicated,meta = (AllowPrivateAccess = "true"))
	TArray<FString> MeshesPlayer;
	UPROPERTY(Replicated,meta = (AllowPrivateAccess = "true"))
	TArray<FString> MeshesFlag;
	UPROPERTY(Replicated,meta = (AllowPrivateAccess = "true"))
	TArray<FString> AnimationPlayer;
	UPROPERTY(Replicated,meta = (AllowPrivateAccess = "true"))
	FString WeaponPath;

	UPROPERTY(BlueprintReadOnly,Replicated,Category="Variaveis")
	float Life = 100;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float Speed;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float BodyAngle;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float CameraAngleX;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float CameraAngleY;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float Direction;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float VelTimerAnimation;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float CheckZAngle = 0.f;
	
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float FireSpeed = 0.05f;
	UPROPERTY(BlueprintReadOnly,Replicated,Category="Variaveis")
	float GunHeatStats = 100.0f;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float DamageAmount = 0.0f;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float MaxSpeed = 1000;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	float TargetRotation;

	UPROPERTY(EditAnywhere,Replicated, meta=(BlueprintProtected = "true"))
	bool HasFlag = false;

	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	TEnumAsByte<StateTypes> CurrentState = Ontheground;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	TEnumAsByte<ActionType> Action = NoCharacterData;
	UPROPERTY(Replicated,BlueprintReadWrite,EditAnywhere, Category="Character")
	TEnumAsByte<NPC_CharacterType> NPC_Character = Junior;

	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	UClass* Junior_Anim;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	UClass* Tecnical_Anim;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	UClass* Senior_Anim;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	UClass* Boss_Anim;

	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	bool BlockTimer = true;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	bool IsCharacterMoving;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	bool CanTarget = false;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	bool AllowFire = true;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	bool HeatedGun = false;

	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	FVector LocalSocketWeapon;

	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	FRotator RotationSocketWeapon;

	void LoadCharacterAssets();

	void CheckChosenCharacter();
	
	void CheckCharacterMesh(float Index);

	UFUNCTION(Reliable,NetMulticast)
	void EnableFlag();
	UFUNCTION(Reliable,NetMulticast)
	void DisableFlag();	

protected:
	virtual void BeginPlay() override;

	//Botões sensíveis, direcional
	void MoveForward(float Value);
	
	void MoveSide(float Value);

	void CheckCameraForward(float Value);

	void CheckCameraSide(float Value);
	
	UFUNCTION(Reliable,Server)
	void CheckCameraForwardServer(float Value);
	UFUNCTION(Reliable,Server)
	void CheckCameraSideServer(float Value);
	UFUNCTION(Reliable,NetMulticast)
	void SetDefaultValuesVel(float Value);

	//Botões apertados
	void CheckJump_Pressed();
	void CheckJump_Released();
	void Fire_Pressed();
	void Fire_Released();
	
	void EnableTarget_Pressed();
	void EnableTarget_Released();

	UFUNCTION(Reliable,Server)
	void EnableTarget_PressedServer();
	UFUNCTION(Reliable,Server)
	void EnableTarget_ReleasedServer();
	
	void Interact_Pressed();
	void Interact_Released();
	void Allow_Fire();

	//Metodos
	void SetDefaultValues();

	void SetState();
	void CreateCameraConfig();
	void CreateCharacterConfig();
	void InitializeCharacterAttachment();
	void CreateProjectile();

	
	
	UFUNCTION(Reliable,Server)
	void CreateProjectileServer(FVector Local,FRotator Rotation);

public:

	virtual void Tick(float DeltaTime) override;
	
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }

	FORCEINLINE class UCameraComponent* GetCamera() const { return MainCamera; }
};
