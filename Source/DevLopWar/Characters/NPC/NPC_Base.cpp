

#include "NPC_Base.h"

#include "BaseAIController.h"
#include "AI/NavigationSystemBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIModule/Classes/AIController.h"
#include "DevLopWar/Characters/Player/Player_Base.h"
#include "Net/UnrealNetwork.h"


ANPC_Base::ANPC_Base()
{
	CheckDefaultValues();
}


void ANPC_Base::BeginPlay()
{
	Super::BeginPlay();
	StartNPC();
}

inline void ANPC_Base::DeleteCounterNPC_Implementation()
{
	FTimerHandle DeathCount;
	GetWorldTimerManager().SetTimer(DeathCount, this, &ANPC_Base::DeleteNPC, 5, false);
}

void ANPC_Base::DeleteNPC_Implementation()
{
	Destroy();
}

void ANPC_Base::ResetNPC_Implementation()
{
	CanMove = true;
	Action = NoCharacterData;
}

void ANPC_Base::StartNPC_Implementation()
{
	AIVariables_BlackBoard = UAIBlueprintHelperLibrary::GetBlackboard(GetController());
	NPCController = Cast<ABaseAIController>(GetController());
	CheckPatrolLocation();
	InitializeCharacterAttachment();
}

void ANPC_Base::InitializeCharacterAttachment_Implementation()
{
	AttackDamage->AttachToComponent(GetMesh(),
						FAttachmentTransformRules::SnapToTargetIncludingScale, "LeftHandSocket");
	GetCharacterMovement()->bUseRVOAvoidance = true;
	GetCharacterMovement()->AvoidanceConsiderationRadius = 500;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->MaxSwimSpeed = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->SetAvoidanceEnabled(true);
}

void ANPC_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetController())
	{
		SetState();
		SetDefaultValuesVel(DeltaTime);
		CheckLife();
		ManageAICharacterVision();
		if (Life > 0 && Action != FallOntheFloor && CurrentState == Ontheground)
		{
			CheckBehaviorFunction();
		}
	}
	else
	{
		if (Action == Dead)
		{
			GetCharacterMovement()->SetCanEverAffectNavigation(false);
			GetCharacterMovement()->SetAvoidanceEnabled(false);
			if (IsValid(EnemyFound))
			{
				EnemyFound = NULL;
			}
			SetActorTickEnabled(false);
		}
	}
}

void ANPC_Base::CheckLife_Implementation()
{
	if (Life <= 0)
	{
		AI_Behavior = Dead_NPC;
		NPCController->StopMovement();
		MaxSpeed = 0;
	}
}

void ANPC_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ANPC_Base::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ANPC_Base, Life);
	DOREPLIFETIME(ANPC_Base, Speed);
	DOREPLIFETIME(ANPC_Base, MaxSpeed);
	DOREPLIFETIME(ANPC_Base, CombatDistance);
	
	DOREPLIFETIME(ANPC_Base, CanMove);
	
	DOREPLIFETIME(ANPC_Base, CurrentState);
	DOREPLIFETIME(ANPC_Base, Action);
	DOREPLIFETIME(ANPC_Base, AI_Behavior);
	
	DOREPLIFETIME(ANPC_Base, AttackDamage);
	DOREPLIFETIME(ANPC_Base, ObjectivePatrolLocation);
}

void ANPC_Base::SetDefaultValuesVel_Implementation(float Value)
{
	if (AI_Behavior == Follow_NPC && Action != Attack && CanMove == true)
	{
		MaxSpeed = 400;
	}
	else if (CanMove == false)
	{
		MaxSpeed = 0;
	}
	else
	{
		MaxSpeed = 100;
	}
	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
	Speed = GetCapsuleComponent()->GetComponentVelocity().GetAbs().X
		+ GetCapsuleComponent()->GetComponentVelocity().GetAbs().Y;
	Speed = FMath::FInterpTo(GetCapsuleComponent()->GetComponentVelocity().Size(),
								  Speed, Value, 10.f);
	
	if (Life <= 0.0f)
	{
		Action = Dead;
		MaxSpeed = 0;
		NPCController->ClearFocus(EAIFocusPriority::Gameplay);
	}
}

void ANPC_Base::CheckDefaultValues()
{
	GetCapsuleComponent()->InitCapsuleSize(29.0f, 76.0f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn,ECR_Ignore);

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -75));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	GetMesh()->SetWorldScale3D(FVector(0.70f, 0.70f, 0.70f));
	GetMesh()->SetCollisionResponseToChannel(ECC_Pawn,ECR_Ignore);

	
	//BaseMesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshContainer(TEXT("SkeletalMesh'/Game/Characters/Clients/Mremireh_O_Desbiens.Mremireh_O_Desbiens'"));
	if (MeshContainer.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshContainer.Object);
	
	}
	AnimationPlayer = "AnimBlueprint'/Game/Characters/Clients/Clients_AnimBlueprint.Clients_AnimBlueprint_C'";
	//AnimBlueprint
	static ConstructorHelpers::FObjectFinder<UClass> AnimFound(*AnimationPlayer);
	GetMesh()->SetAnimInstanceClass(AnimFound.Object);

	//floats
	Life = 20;
	CombatDistance = 100;

	//Structs
	Action = NoCharacterData;
	CurrentState = Ontheground;
	AI_Behavior = Patrol_NPC;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	
	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ABaseAIController::StaticClass();
	
	AttackDamage = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollision"));
	AttackDamage->bFillCollisionUnderneathForNavmesh = false;
	AttackDamage->bHiddenInGame = false;
	AttackDamage->SetVisibility(true);
	AttackDamage->SetCanEverAffectNavigation(false);
	AttackDamage->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f));
	AttackDamage->SetRelativeRotation(FRotator(0, 0, 0));
	AttackDamage->SetWorldScale3D(FVector(1, 0.5, 2));
	AttackDamage->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	AttackDamage->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	AttackDamage->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	AttackDamage->OnComponentBeginOverlap.AddDynamic(this, &ANPC_Base::StartDamageCollision);
	AttackDamage->OnComponentEndOverlap.AddDynamic(this, &ANPC_Base::EndDamageCollision);
}

void ANPC_Base::SetState_Implementation()
{
	if (GetCharacterMovement()->MovementMode == MOVE_Falling)
	{
		CurrentState = StateTypes::Falling;
	}
	else if (GetCharacterMovement()->MovementMode == MOVE_Flying)
	{
		CurrentState = Flying;
	}
	else if (GetCharacterMovement()->MovementMode == MOVE_Walking)
	{
		CurrentState = Ontheground;
	}
	else
	{
		CurrentState = Ontheground;
	}
}

void ANPC_Base::CheckPatrolLocation_Implementation()
{
	if (IsValid(AIVariables_BlackBoard))
	{
		AIVariables_BlackBoard->SetValueAsVector("ObjectiveLocation", ObjectivePatrolLocation->GetActorLocation());
	}
}

void ANPC_Base::MoveCharacterPatrol_Implementation(FVector PatrolLocation)
{
	if (AI_Behavior == Patrol_NPC)
	{
		CheckPatrolLocation();
		if (FVector::Dist(PatrolLocation, GetActorLocation()) >= CombatDistance)
		{
			NPCController->MoveToLocation(PatrolLocation, 25, true, true,
												false, false, 0, false);
			if (FVector::Dist(PatrolLocation, GetActorLocation()) <= 130 && Action != Attack && CanMove == true)
			{
				CanMove = false;
				Action = Attack;
				AIVariables_BlackBoard->SetValueAsEnum("Action", Action);
				FTimerHandle LocalTimer;
				GetWorldTimerManager().SetTimer(LocalTimer, this, &ANPC_Base::ResetNPC, 5, false);
			}
		}
	}
	else if (AI_Behavior == Follow_NPC)
	{
		if (FVector::Dist(EnemyFound->GetActorLocation(), GetActorLocation()) >= CombatDistance)
		{
			Action = NoCharacterData;
			AIVariables_BlackBoard->SetValueAsEnum("Action", Action);
			NPCController->MoveToLocation(EnemyFound->GetActorLocation(), 25, true, true,
											true, false, 0, false);
			NPCController->ClearFocus(EAIFocusPriority::Default);
		}
		else if (FVector::Dist(EnemyFound->GetActorLocation(), GetActorLocation()) <= CombatDistance)
		{
			CanMove = false;
			Action = Attack;
			AIVariables_BlackBoard->SetValueAsEnum("Action", Action);
			NPCController->SetFocus(EnemyFound);
			FTimerHandle LocalTimer;
			GetWorldTimerManager().SetTimer(LocalTimer, this, &ANPC_Base::ResetNPC, 5, false);
		}
	}
}

void ANPC_Base::CheckBehaviorFunction_Implementation()
{
	if (IsValid(NPCController))
	{
		if (CurrentState == Ontheground)
		{
			if (AI_Behavior == Patrol_NPC)
			{
				MoveCharacterPatrol(AIVariables_BlackBoard->GetValueAsVector("ObjectiveLocation"));
			}
			if (AI_Behavior == Follow_NPC)
			{
				if (IsValid(EnemyFound))
				{
					MoveCharacterPatrol(EnemyFound->GetActorLocation());
				}
			}
		}
		else{
			NPCController->ClearFocus(EAIFocusPriority::Gameplay);
			GetCharacterMovement()->StopActiveMovement();
			NPCController->StopMovement();
			Action = NoCharacterData;
		}
	}
}

void ANPC_Base::ManageAIChosenEnemy()
{
	APlayer_Base* DefaultPlayer = Cast<APlayer_Base>(EnemyFound);

	if (IsValid(DefaultPlayer))
	{
		AIVariables_BlackBoard->SetValueAsObject("Enemy", DefaultPlayer);
	}
}

void ANPC_Base::ManageAICharacterVision_Implementation()
{
	if (Life > 0 && Action != FallOntheFloor && CurrentState == Ontheground)
	{
		if (EnemyFound)
		{
			float AuxDistancia = GetDistanceTo(EnemyFound);
			if (AuxDistancia < 3000)
			{
				AIVariables_BlackBoard->SetValueAsFloat("ObjectiveDistance", AuxDistancia);
				AI_Behavior = Follow_NPC;
				AIVariables_BlackBoard->SetValueAsEnum("AI_Behavior", AI_Behavior);
			}
			else
			{
				EnemyFound = NULL;
				AIVariables_BlackBoard->ClearValue("Enemy");
				AI_Behavior = Patrol_NPC;
				AIVariables_BlackBoard->SetValueAsEnum("AI_Behavior", AI_Behavior);
			}
		}
	}
	if (IsValid(EnemyFound))
	{
		APlayer_Base* DefaultPlayer = Cast<APlayer_Base>(EnemyFound);
		if (IsValid(DefaultPlayer))
		{
			if (DefaultPlayer->Life <= 0)
			{
				EnemyFound = NULL;
				NPCController->ClearFocus(EAIFocusPriority::Gameplay);
				AIVariables_BlackBoard->ClearValue("Enemy");
				Action = NoCharacterData;
				AIVariables_BlackBoard->SetValueAsEnum("Action", Action);
				AI_Behavior = Patrol_NPC;
				AIVariables_BlackBoard->SetValueAsEnum("AI_Behavior", AI_Behavior);
			}
		}
	}
}
