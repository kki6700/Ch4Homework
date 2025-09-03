// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HMChatting : ModuleRules
{
	public HMChatting(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		PrivateDependencyModuleNames.AddRange(new string[] {  "UMG", "Slate",  "SlateCore" });

		PublicIncludePaths.AddRange(new string[] { "HMChatting"});
	}
}
