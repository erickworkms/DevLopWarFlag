

#include "ProjectileCsharp.h"

AProjectileCsharp::AProjectileCsharp()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		ProjectileContainer(
			TEXT("StaticMesh'/Game/Characters/Weapon/csharp.csharp'"));
	if (ProjectileContainer.Succeeded())
	{
		ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshProjectile"));
		ProjectileMesh->SetStaticMesh(ProjectileContainer.Object);
		ProjectileMesh->SetSimulatePhysics(true);
		ProjectileMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
		SetRootComponent(ProjectileMesh);

		Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
		Projectile->SetUpdatedComponent(ProjectileMesh);
		Projectile->InitialSpeed = 3000.f;
		Projectile->MaxSpeed = 3000.f;
		Projectile->bRotationFollowsVelocity = true;
		Projectile->bShouldBounce = false;
		Projectile->bSimulationEnabled = true;
		ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::StartDamageCollision);
		bReplicates = true;
	}
}
