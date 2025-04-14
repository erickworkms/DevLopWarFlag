

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "DevLopWar/Characters/Player/Player_Base.h"
#include "GameFramework/Actor.h"


void APlayer_Base::SetDefaultValues()
{
	MeshesPlayer.Init("4", 4);
	AnimationPlayer.Init("4", 4);
	MeshesFlag.Init("4", 4);
	
	MeshesPlayer[0] = TEXT("SkeletalMesh'/Game/Characters/Junior/Junior.Junior'");
	MeshesPlayer[1] = TEXT("SkeletalMesh'/Game/Characters/Tecnical/Sporty_Granny.Sporty_Granny'");
	MeshesPlayer[2] = TEXT("SkeletalMesh'/Game/Characters/Senior/Swat.Swat'");
	MeshesPlayer[3] = TEXT("SkeletalMesh'/Game/Characters/Boss/The_Boss.The_Boss'");

	MeshesFlag[0] = TEXT("StaticMesh'/Game/Characters/Weapon/nocode.nocode'");
	MeshesFlag[1] = TEXT("StaticMesh'/Game/Characters/Weapon/csharp.csharp'");
	MeshesFlag[2] = TEXT("StaticMesh'/Game/Characters/Weapon/java.java'");
	MeshesFlag[3] = TEXT("StaticMesh'/Game/Characters/Weapon/cplusplus.cplusplus'");
	
	WeaponPath = TEXT("SkeletalMesh'/Game/Characters/Weapon/Weapon.Weapon'");
	
	AnimationPlayer[0] = TEXT("AnimBlueprint'/Game/Characters/Junior/Junior_AnimBlueprint.Junior_AnimBlueprint_C'");
	AnimationPlayer[1] = TEXT("AnimBlueprint'/Game/Characters/Tecnical/Tecnical_AnimBlueprint.Tecnical_AnimBlueprint_C'");
	AnimationPlayer[2] = TEXT("AnimBlueprint'/Game/Characters/Senior/Senior_AnimBlueprint.Senior_AnimBlueprint_C'");
	AnimationPlayer[3] = TEXT("AnimBlueprint'/Game/Characters/Boss/Boss_AnimBlueprint.Boss_AnimBlueprint_C'");


	Junior_Anim = Cast<UClass>(StaticLoadObject(UClass::StaticClass(),NULL, *AnimationPlayer[0]));
	Tecnical_Anim = Cast<UClass>(StaticLoadObject(UClass::StaticClass(),NULL, *AnimationPlayer[1]));
	Senior_Anim = Cast<UClass>(StaticLoadObject(UClass::StaticClass(),NULL, *AnimationPlayer[2]));
	Boss_Anim = Cast<UClass>(StaticLoadObject(UClass::StaticClass(),NULL, *AnimationPlayer[3]));
}

void APlayer_Base::CheckCharacterMesh(float Index)
{
	if (IsValid(Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(),NULL, *MeshesPlayer[Index]))) &&
		IsValid(Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(),NULL, *WeaponPath))))
	{
		
		GetMesh()->SetSkeletalMesh(
		Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(),NULL, *MeshesPlayer[Index])));
		Weapon->SetSkeletalMesh(
			Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(),NULL, *WeaponPath)));
		Flag->SetStaticMesh(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(),NULL, *MeshesFlag[Index])));
		Flag->SetVisibility(false);
		InitializeCharacterAttachment();
	}
	
}
void APlayer_Base::CreateCharacterConfig()
{
	bReplicates = true;
	SetReplicateMovement(true);
	
	GetCapsuleComponent()->InitCapsuleSize(29.0f, 76.0f);
	
	//BaseMesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshContainer(TEXT("SkeletalMesh'/Game/Characters/Junior/Junior.Junior'"));
	if (MeshContainer.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshContainer.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -75));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		GetMesh()->SetWorldScale3D(FVector(0.70f, 0.70f, 0.70f));
	}

	//AnimBlueprint
	static ConstructorHelpers::FObjectFinder<UClass> AnimFound(TEXT("AnimBlueprint'/Game/Characters/Junior/Junior_AnimBlueprint.Junior_AnimBlueprint_C'"));
	GetMesh()->SetAnimInstanceClass(AnimFound.Object);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Flag = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Flag"));
}

void APlayer_Base::InitializeCharacterAttachment()
{
	Weapon->SetSkeletalMesh(Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(),NULL, *WeaponPath)));
	Weapon->AttachToComponent(GetMesh(),
						FAttachmentTransformRules::SnapToTargetIncludingScale, "RightHandSocket");
	Weapon->SetRelativeLocationAndRotation(FVector(0, 0, 0),
										 FRotator(0, 0, 0), false, false);

	
	Flag->AttachToComponent(GetMesh(),
						FAttachmentTransformRules::SnapToTargetIncludingScale, "BackSocket");
	Flag->SetRelativeLocationAndRotation(FVector(0, 0, 0),
										 FRotator(0, 0, 0), false, false);
}
