

#include "BaseAIController.h"

#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "DevLopWar/Characters/Player/Player_Base.h"
#include "Perception/AIPerceptionComponent.h"
#include "Navigation/PathFollowingComponent.h"


ABaseAIController::ABaseAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	bStartAILogicOnPossess = true;

	AutoReceiveInput = EAutoReceiveInput::Disabled;
	Possess(GetPawn());
	BehaviorTreePath = TEXT(
		"BehaviorTree'/Game/Characters/Clients/Clients_BehaviorTree.Clients_BehaviorTree'");
	
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		BehaviorTreePathFound(TEXT("BehaviorTree'/Game/Characters/Clients/Clients_BehaviorTree.Clients_BehaviorTree'"));
	BehaviorTree = BehaviorTreePathFound.Object;
	
	static ConstructorHelpers::FObjectFinder<UBlackboardData>
		CaminhoData(TEXT(
			"BlackboardData'/Game/Characters/Clients/ClientsAI_VariableList.ClientsAI_VariableList'"));
	Variables_AI_Data = CaminhoData.Object;

	Variables_AI_Comp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Variables_AI_Comp"));
	
	AddAI_Variables();
	
	Variables_AI_Comp->InitializeBlackboard(*Variables_AI_Data);
	
	UseBlackboard(Variables_AI_Data, Variables_AI_Comp);
	
	Variables_AI_Comp->SetValueAsObject("SelfActor", GetPawn());
	
	Detector = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Sensor"));
	ConfigDetector = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("ConfigSensor"));
	
	SensorDefaultValues();
}

UAIPerceptionComponent* ABaseAIController::GetPerceptionComponent()
{
	return Super::GetPerceptionComponent();
}

void ABaseAIController::SensorDefaultValues()
{
	ConfigDetector->SightRadius = 2000.f;
	ConfigDetector->Implementation = UAISense_Sight::StaticClass();
	ConfigDetector->LoseSightRadius = 1100.f;
	ConfigDetector->PeripheralVisionAngleDegrees = 60.f;
	ConfigDetector->SetMaxAge(2.f);
	ConfigDetector->AutoSuccessRangeFromLastSeenLocation = -1.f;
	ConfigDetector->DetectionByAffiliation.DetectAllFlags();
	ConfigDetector->DetectionByAffiliation.bDetectNeutrals = true;
	ConfigDetector->DetectionByAffiliation.bDetectEnemies = true;
	ConfigDetector->DetectionByAffiliation.bDetectFriendlies = true;

	Detector->ConfigureSense(*ConfigDetector);
	Detector->SetDominantSense(ConfigDetector->GetSenseImplementation());
}

void ABaseAIController::InitializeSensor()
{
	Detector = GetPerceptionComponent();

	Detector->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseAIController::DetectPresence);

	Detector->UpdatePerceptionWhitelist(ConfigDetector->GetSenseID(), true);
}

void ABaseAIController::AddAI_Variables()
{
	Variables_AI_Data->UpdatePersistentKey<UBlackboardKeyType_Object>(FName("SelfActor"));
	Variables_AI_Data->UpdatePersistentKey<UBlackboardKeyType_Object>(FName("Enemy"));

	Variables_AI_Data->UpdatePersistentKey<UBlackboardKeyType_Enum>(FName("Action"));
	Variables_AI_Data->UpdatePersistentKey<UBlackboardKeyType_Enum>(FName("CurrentState"));
	Variables_AI_Data->UpdatePersistentKey<UBlackboardKeyType_Enum>(FName("AI_Behavior"));

	Variables_AI_Data->UpdatePersistentKey<UBlackboardKeyType_Vector>(FName("ObjectiveLocation"));

	Variables_AI_Data->UpdatePersistentKey<UBlackboardKeyType_Float>(FName("ObjectiveDistance"));
}

void ABaseAIController::DetectPresence(AActor* ChosenCharacter, FAIStimulus Stimulus)
{
	if (IsValid(NPC_Ref))
	{
		if (Stimulus.Type == 0 && NPC_Ref->EnemyFound == NULL)
		{
			APlayer_Base* DefaultPlayer = Cast<APlayer_Base>(ChosenCharacter);

			if (DefaultPlayer)
			{
				if (!IsValid(NPC_Ref->EnemyFound))
				{
					NPC_Ref->EnemyFound = DefaultPlayer;
					NPC_Ref->ManageAIChosenEnemy();
				}
			}
		}
	}else if (!IsValid(NPC_Ref))
	{
		NPC_Ref = Cast<ANPC_Base>(GetPawn());
	}
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
	NPC_Ref = Cast<ANPC_Base>(GetPawn());
	InitializeSensor();
	RunBehaviorTree(BehaviorTree);
}
