// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DevLopWar : ModuleRules
{
	public DevLopWar(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem", "Networking", "JsonUtilities" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","UMG", "Slate", "SlateCore", "OnlineSubsystem","HTTP","Json","Sockets"});
	}
}
