// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Player/HMPlayerController.h"
#include "HMGameModeBase.generated.h"

class AHMPlayerController;
/**
 * 
 */
UCLASS()
class HMCHATTING_API AHMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


public:
	virtual void OnPostLogin(AController* NewPlayer) override;

	virtual  void BeginPlay() override;

	void PrintChatMessageString(AHMPlayerController* InChattingPlayerController, const FString& InChatMessageString);

	FString GenerateSecretNumber();

	bool IsGuessNumberString(const FString& InNumberString);

	FString JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString);

	void IncrementGuessCount(AHMPlayerController* InChattingPlayerPlayerController);

	void ResetGame();
	void JudgeGame(AHMPlayerController* InChattingPlayerController, int InStrikeCount);

public:
	FString SecretNumberString;

	TArray<TObjectPtr<AHMPlayerController>> AllPlayerControllers;
};
