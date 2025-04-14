#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum StateTypes
{
	Ontheground UMETA(DisplayName = "Ontheground"),
	Falling UMETA(DisplayName = "Falling"),
	Flying UMETA(DisplayName = "Flying")
};

UENUM(BlueprintType)
enum ActionType
{
	Attack UMETA(DisplayName = "Attack"),
	JumpAction UMETA(DisplayName = "Jump"),
	TakeDamage UMETA(DisplayName = "TakeDamage"),
	FallOntheFloor UMETA(DisplayName = "FallOntheFloor"),
	Dead UMETA(DisplayName = "Dead"),
	NoCharacterData UMETA(DisplayName = "NoCharacterData")
};

UENUM(BlueprintType)
enum NPC_CharacterType
{
	Boss UMETA(DisplayName = "Boss"),
	Senior UMETA(DisplayName = "Senior"),
	Tecnical UMETA(DisplayName = "Tecnical"),
	Junior UMETA(DisplayName = "Junior"),
	NoJob UMETA(DisplayName = "NoJob")
};

UENUM(BlueprintType)
enum AI_StateType
{
	Follow_NPC UMETA(DisplayName = "Following"),
	Patrol_NPC UMETA(DisplayName = "Patrol"),
	Idle_NPC UMETA(DisplayName = "Idle"),
	FallOntheFloor_NPC UMETA(DisplayName = "FallOntheFloor"),
	TakeDamage_NPC UMETA(DisplayName = "TakeDamage"),
	Dead_NPC UMETA(DisplayName = "Dead"),
	Rest_NPC UMETA(DisplayName = "Rest"),
	NoCharacterData_NPC UMETA(DisplayName = "NoCharacterData")
};