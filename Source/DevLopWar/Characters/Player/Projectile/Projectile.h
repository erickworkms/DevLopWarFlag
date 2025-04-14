

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class DEVLOPWAR_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	AActor* ProjectileOwner;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	UProjectileMovementComponent* Projectile;
	UPROPERTY(Replicated, meta=(BlueprintProtected = "true"))
	UStaticMeshComponent* ProjectileMesh;
	
	UFUNCTION(Reliable,Server)
	void AttackDamageProjectile(AActor* DetectedEnemy);

	UFUNCTION()
	void StartDamageCollision(UPrimitiveComponent* OverlappedComp, AActor* DetectedEnemy,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult)
	{
		if(IsValid(ProjectileOwner))
		{
			if(DetectedEnemy != this && DetectedEnemy != ProjectileOwner)
			{
				AttackDamageProjectile(DetectedEnemy);
			}
		}
	}
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
