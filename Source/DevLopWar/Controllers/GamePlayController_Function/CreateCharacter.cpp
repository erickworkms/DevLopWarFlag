

#include "EngineUtils.h"
#include "DevLopWar/GameModes/DevLopWarGameMode.h"
#include "GameFramework/PlayerStart.h"
#include "Delegates/DelegateSignatureImpl.inl"


void AGamePlayController::CreateCharacter_Implementation()
{
	UWorld* World = GetWorld();
	check(World);
	TArray<AActor*> PlayerStartFound;
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		PlayerStartFound.Add(*It);
	}
	APlayerStart* ChosenPoint = nullptr;
	if (PlayerStartFound.Num() > 0)
	{
		ChosenPoint = Cast<APlayerStart>(
			PlayerStartFound[FMath::RandRange(0, PlayerStartFound.Num() - 1)]);
	}
	if (ChosenPoint)
	{
		BaseCharacter = GetWorld()->SpawnActorDeferred<APlayer_Base>(
			APlayer_Base::StaticClass(),
			FTransform(ChosenPoint->GetActorRotation(),
					   ChosenPoint->GetActorLocation()));
		if (BaseCharacter)
		{
			BaseCharacter->FinishSpawning(FTransform(ChosenPoint->GetActorRotation(),
												  ChosenPoint->GetActorLocation()));
		}
		bShowMouseCursor = false;
		SetPawn(BaseCharacter);
		Possess(BaseCharacter);
		AddDataInstanceServer();
	}
}
