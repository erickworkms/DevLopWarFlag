

#include "DevLopWarGameInstance.h"

#include "Net/UnrealNetwork.h"


void UDevLopWarGameInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UDevLopWarGameInstance,PlayerController);
	DOREPLIFETIME(UDevLopWarGameInstance,PlayerIndex);
	DOREPLIFETIME(UDevLopWarGameInstance,Team);
}
