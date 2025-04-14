


#include "BaseHudGameplay.h"

#include "Net/UnrealNetwork.h"

void ABaseHudGameplay::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABaseHudGameplay,HudGameplay);
}
