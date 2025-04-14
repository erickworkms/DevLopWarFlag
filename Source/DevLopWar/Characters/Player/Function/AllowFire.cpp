
#include "DevLopWar/Characters/Player/Player_Base.h"

void APlayer_Base::Allow_Fire()
{
	if (AllowFire == false && CanTarget == true && HeatedGun == false)
	{
		CreateProjectile();
		GetWorldTimerManager().SetTimer(ProjectileTimer, this, &APlayer_Base::Allow_Fire, FireSpeed, false);
		GunHeatStats -= FireSpeed * 30;
		if (GunHeatStats <= 0.0f)
		{
			HeatedGun = true;
		}
	}
	else if (CanTarget == false)
	{
		AllowFire = true;
	}
}
