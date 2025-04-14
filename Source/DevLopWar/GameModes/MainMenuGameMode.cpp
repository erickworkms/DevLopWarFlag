

#include "MainMenuGameMode.h"
#include "DevLopWar/GameInstance/DevLopWarGameInstance.h"
#include "GameFramework/HUD.h"
#include "OnlineSubsystemClasses.h"
#include "SocketSubsystem.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "Kismet/GameplayStatics.h"
#include "Misc/OutputDeviceNull.h"


AMainMenuGameMode::AMainMenuGameMode()
{
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDClass(TEXT("/Game/Maps/HudMainMenu"));
	if (PlayerHUDClass.Succeeded())
	{
		HUDClass = PlayerHUDClass.Class;
	}
}

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);

	if (Controller)
	{
		Controller->bShowMouseCursor = true;
		Controller->DefaultMouseCursor = EMouseCursor::Crosshairs;
		GameInstance = Cast<UDevLopWarGameInstance>(GetWorld()->GetGameInstance());
	}
	
	FOutputDeviceNull Out;
	bool bCanBindAll = false;
	TSharedRef<FInternetAddr> LocalIP = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(Out, bCanBindAll);
	
	if (LocalIP->IsValid() && IsValid(GameInstance))
	{
		GameInstance->ip = LocalIP->ToString(false);
		UE_LOG(LogTemp, Warning, TEXT("IP Local: %s"), *GameInstance->ip);
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow,*GameInstance->ip);
	}
}


void AMainMenuGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}


void AMainMenuGameMode::LogoutPlayer(APlayerController* Controller)
{
	UKismetSystemLibrary::QuitGame(GetWorld(), Controller, EQuitPreference::Quit, false);
}


