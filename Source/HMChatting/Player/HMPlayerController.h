// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HMPlayerController.generated.h"


class UHMChatInput;
/**
 * 
 */
UCLASS()
class HMCHATTING_API AHMPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AHMPlayerController();

	virtual  void BeginPlay() override;

	void SetChatMessageString(const FString& InChatMessageString);

	void PrintChatMessageString(const FString& InChatMessageString);

	UFUNCTION(Client, Reliable)
	void ClientRPCPrintChatMessageString(const FString& InChatMessageString);

	UFUNCTION(Server, Reliable)
	void ServerRPCPrintChatMessageString(const FString& InChatMessageString);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHMChatInput>ChatInputWidgetClass;

	UPROPERTY()
	TObjectPtr<UHMChatInput>ChatInputWidgetInstance;
	FString ChatMessageString;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> NotificationTextWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> NotificationIconWidgetInstance;

public:
	UPROPERTY(Replicated, BlueprintReadOnly)
	FText NotificationText;
	
};
