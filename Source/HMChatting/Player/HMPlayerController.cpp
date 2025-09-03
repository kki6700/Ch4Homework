// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HMPlayerController.h"
#include "Player/HMPlayerState.h"
#include "UI/HMChatInput.h"
#include "HMChatting.h"
#include "Kismet/GameplayStatics.h"
#include "Game/HMGameModeBase.h"
#include "Net/UnrealNetwork.h"


AHMPlayerController::AHMPlayerController()
{
	bReplicates = true;
	
}

void AHMPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() == false)
	{
		return;
	}

	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);
	if (IsValid(ChatInputWidgetClass)==true)
	{
		ChatInputWidgetInstance = CreateWidget<UHMChatInput>(this,ChatInputWidgetClass);
		if (IsValid(ChatInputWidgetInstance) == true)
		{
			ChatInputWidgetInstance -> AddToViewport();
		}
	}
	if (IsValid(NotificationTextWidgetClass)==true)
	{
		NotificationIconWidgetInstance = CreateWidget<UUserWidget>(this,NotificationTextWidgetClass);
		if (IsValid(NotificationIconWidgetInstance) == true)
		{
			NotificationIconWidgetInstance -> AddToViewport();
		}
	}
}

void AHMPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;

	if (IsLocalController() == true)
	{
		AHMPlayerState* HMPS = GetPlayerState<AHMPlayerState>();
		if (IsValid(HMPS) == true)
		{
			FString CombinedMessageString = HMPS -> GetPlayerInfoString() + TEXT(": ") + InChatMessageString;
			ServerRPCPrintChatMessageString(CombinedMessageString);
			
		}
	}
}

void AHMPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}

void AHMPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (IsValid(GM) == true)
	{
		AHMGameModeBase* HMGM = Cast<AHMGameModeBase>(GM);
		if (IsValid(HMGM) == true)
		{
			HMGM -> PrintChatMessageString(this,InChatMessageString);
		}
	}
}

void AHMPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	HMChatFuntionKibrary::MyPrintString(this,InChatMessageString,10.f);
}

void AHMPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, NotificationText);
	
}
