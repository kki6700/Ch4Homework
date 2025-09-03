// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class HMChatFuntionKibrary
{
public:
	static void MyPrintString(const AActor* InWorldConextActor, const FString& InString, float InTimeToDelay = 1.f, FColor InColor = FColor:: Cyan)
	{
		if (IsValid(GEngine) == true && IsValid(InWorldConextActor) == true)
		{
			if (InWorldConextActor -> GetNetMode() == NM_Client || InWorldConextActor -> GetNetMode() == NM_ListenServer)
			{
				GEngine -> AddOnScreenDebugMessage(-1, InTimeToDelay, InColor, InString);
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("%s"), *InString);
			}
		}
		
	}
	static FString GetNetModeString(const AActor* InWorldConextActor)
	{
		FString NetModeString = TEXT("None");
		if (IsValid(InWorldConextActor) == true)
		{
			ENetMode NetMode = InWorldConextActor -> GetNetMode();
			if (NetMode == NM_Client)
			{
				NetModeString = TEXT("Client");
			}
			else
			{
				if (NetMode == NM_Standalone)
				{
					NetModeString = TEXT("Standalone");
				}
				else
				{
					NetModeString = TEXT("Server");
				}
			}
		}
		return NetModeString;
	}
	static FString GetRoleString (const AActor* InActor)
	{
		FString RoleString = TEXT("None");

		if (IsValid(InActor) == true)
		{
			FString LocalRoleString = UEnum:: GetValueAsString(TEXT("Engine.ENetRole"), InActor->GetLocalRole());
			FString RemateRoleString = UEnum:: GetValueAsString(TEXT("Engine.ENetRole"),InActor -> GetLocalRole());

			RoleString = FString::Printf(TEXT("%s%s"), *LocalRoleString, *RemateRoleString);
		}
		return RoleString;
	}
};