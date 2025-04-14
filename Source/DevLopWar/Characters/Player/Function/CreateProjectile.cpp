

#include "Components/SkeletalMeshComponent.h"
#include "DevLopWar/Characters/Enums/EnumList.h"
#include "DevLopWar/Characters/Player/Player_Base.h"
#include "DevLopWar/Characters/Player/Projectile/ProjectileCPlus.h"
#include "DevLopWar/Characters/Player/Projectile/ProjectileCsharp.h"
#include "DevLopWar/Characters/Player/Projectile/ProjectileJava.h"
#include "DevLopWar/Characters/Player/Projectile/ProjectileNoCode.h"


void APlayer_Base::CreateProjectile()
{
	LocalSocketWeapon = Weapon->GetSocketLocation("FireSocket");
	RotationSocketWeapon = Weapon->GetSocketRotation("FireSocket");
	
	CreateProjectileServer(LocalSocketWeapon,RotationSocketWeapon);
}

void APlayer_Base::EnableFlag_Implementation()
{
	Flag->SetVisibility(true);
	
}

void APlayer_Base::DisableFlag_Implementation()
{
	Flag->SetVisibility(false);
}


void APlayer_Base::CreateProjectileServer_Implementation(FVector Local,FRotator Rotation)
{
	AProjectileNoCode* ProjectileJunior;
	AProjectileCsharp* ProjectileTecnical;
	AProjectileJava* ProjectileSenior;
	AProjectileCMais* ProjectileBoss;

	
	switch (NPC_Character)
	{
	case Junior:
		DamageAmount = 10;
		FireSpeed = 0.5;
		ProjectileJunior = GetWorld()->SpawnActor<AProjectileNoCode>(
			Local, Rotation);
		ProjectileJunior->ProjectileOwner = this;
		break;
	case Tecnical:
		DamageAmount = 10;
		FireSpeed = 0.2;
		ProjectileTecnical = GetWorld()->SpawnActor<AProjectileCsharp>(Local, Rotation);
		ProjectileTecnical->ProjectileOwner = this;
		break;
	case Senior:
		DamageAmount = 5;
		FireSpeed = 0.1;
		ProjectileSenior = GetWorld()->SpawnActor<AProjectileJava>(Local, Rotation);
		ProjectileSenior->ProjectileOwner = this;
		break;
	case Boss:
		DamageAmount = 50;
		FireSpeed = 1;
		ProjectileBoss = GetWorld()->SpawnActor<AProjectileCMais>(Local, Rotation);
		ProjectileBoss->ProjectileOwner = this;
		break;
	default:
		FireSpeed = 0.1;
		ProjectileSenior = GetWorld()->SpawnActor<AProjectileJava>(Local, Rotation);
		ProjectileSenior->ProjectileOwner = this;
		break;
	}
}
