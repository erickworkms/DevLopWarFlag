
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPC_Base.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPWAR_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABaseAIController();
	
	FString BehaviorTreePath;
	UPROPERTY()
	UBehaviorTree* BehaviorTree;
	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* Detector;
	UPROPERTY()
	UAISenseConfig_Sight* ConfigDetector;
	UPROPERTY()
	UBlackboardComponent* Variables_AI_Comp;
	UPROPERTY()
	UBlackboardData* Variables_AI_Data;
	UPROPERTY()
	ANPC_Base* NPC_Ref;


	virtual UAIPerceptionComponent* GetPerceptionComponent() override;

	void SensorDefaultValues();
	void InitializeSensor();
	void AddAI_Variables();
	UFUNCTION()
	void DetectPresence(AActor* Per,FAIStimulus Stimulus);
protected:

	virtual void BeginPlay() override;
};
