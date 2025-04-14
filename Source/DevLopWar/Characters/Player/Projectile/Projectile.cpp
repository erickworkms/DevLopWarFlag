
#include "Projectile.h"

#include "DevLopWar/GameModes/DevLopWarGameMode.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "Net/UnrealNetwork.h"

// Sets default values
AProjectile::AProjectile()
{
	bReplicates = true;
}


void AProjectile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AProjectile, ProjectileOwner);
	DOREPLIFETIME(AProjectile, Projectile);
	DOREPLIFETIME(AProjectile, ProjectileMesh);
}

void AProjectile::AttackDamageProjectile_Implementation(AActor* DetectedEnemy)
{
	AGameModeBase* GameModeFound = GetWorld()->GetAuthGameMode();
	ADevLopWarGameMode* GameMode = Cast<ADevLopWarGameMode>(GameModeFound);
	GameMode->AttackDamageProjectile(ProjectileOwner,DetectedEnemy,this);
}
