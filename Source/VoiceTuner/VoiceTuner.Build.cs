// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class VoiceTuner : ModuleRules
{
	public VoiceTuner(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "HTTP", "Json", "JsonUtilities", "SlateCore", "OnlineSubsystem", "OnlineSubsystemSteam","UMG" });
	}
}
