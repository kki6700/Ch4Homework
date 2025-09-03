// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HMGameModeBase.h"
#include "HMGameStateBase.h"
#include "EngineUtils.h"
#include "Player/HMPlayerController.h"
#include "Player/HMPlayerState.h"

void AHMGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	AHMPlayerController* HMPlayerController = Cast<AHMPlayerController>(NewPlayer);
	if (IsValid(HMPlayerController) == true)
	{
		HMPlayerController -> NotificationText = FText :: FromString(TEXT("Connected to the Server"));
		AllPlayerControllers.Add(HMPlayerController);

		AHMPlayerState * HMPS = HMPlayerController -> GetPlayerState<AHMPlayerState>();
		if (IsValid(HMPS) == true)
		{
			HMPS -> PlayerNameString = TEXT("Player") + FString::FromInt(AllPlayerControllers.Num());
			
		}
		AHMGameStateBase* HMGameStateBase = GetGameState<AHMGameStateBase>();
		if (IsValid(HMGameStateBase) == true)
		{
			HMGameStateBase -> MulticastRPCBroadcastLoginMessage(HMPS -> PlayerNameString);
			
		}
	}
}

void AHMGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	SecretNumberString = GenerateSecretNumber();
	UE_LOG(LogTemp,Error,TEXT("Secret Number is %s"),*SecretNumberString);
}

void AHMGameModeBase::PrintChatMessageString(AHMPlayerController* InChattingPlayerController, const FString& InChatMessageString)
{
	FString ChatMessageString = InChatMessageString;
	int Index = InChatMessageString.Len() - 3;

	FString GuessMumberString = InChatMessageString.RightChop(Index);

	if (IsGuessNumberString(GuessMumberString) == true)
	{
		FString JudgeResultString = JudgeResult(SecretNumberString, GuessMumberString);
		IncrementGuessCount(InChattingPlayerController);
		for (TActorIterator<AHMPlayerController>It(GetWorld()); It; ++It)
		{
			AHMPlayerController* HMPlayerController = *It;
			if (IsValid(HMPlayerController) == true)
			{
				FString CombinedMEssageString = InChatMessageString + TEXT(" ") + JudgeResultString;
				HMPlayerController -> ClientRPCPrintChatMessageString(CombinedMEssageString);

				int32 StrikeCount = FCString :: Atoi(*JudgeResultString.Left(1));
				JudgeGame(InChattingPlayerController, StrikeCount);
				
			}
		}
	}
	else
	{
		for (TActorIterator<AHMPlayerController> It(GetWorld()); It; ++It)
		{
			AHMPlayerController* HMPlayerController = *It;
			if (IsValid(HMPlayerController) == true)
			{
				HMPlayerController -> ClientRPCPrintChatMessageString(InChatMessageString);
				
			}
		}
	}
}

void AHMGameModeBase::IncrementGuessCount(AHMPlayerController* InChattingPlayerPlayerController)
{
	AHMPlayerState* HMPS = InChattingPlayerPlayerController -> GetPlayerState<AHMPlayerState>();
	if (IsValid(HMPS) == true)
	{
		HMPS -> CurrentGuesssCount++;
		
	}
}

FString AHMGameModeBase::GenerateSecretNumber()
{
	TArray<int32> Numbers;

	for (int32 i = 1; i<= 9; ++i)
	{
		Numbers.Add(i);
	}

	FMath:: RandInit(FDateTime:: Now().GetTicks());
	Numbers = Numbers.FilterByPredicate([](int32 Num){return Num > 0;});
	FString Result;

	for (int32 i = 0; i < 3; ++i)
	{
		int32 Index = FMath:: RandRange(0, Numbers.Num() - 1);
		Result.Append(FString:: FromInt(Numbers[Index]));
		Numbers.RemoveAt(Index);
	}
	return Result;
	
}

bool AHMGameModeBase::IsGuessNumberString(const FString& InNumberString)
{
	bool bCanPlay = false;

	do
	{
		if (InNumberString.Len() != 3)
		{
			break;
			
		}
		bool bIsUniqe = true;
		TSet<TCHAR>UniqueDigits;
		for (TCHAR C: InNumberString)
		{
			if (FChar::IsDigit(C) == false || false || C== '0')
			{
				bIsUniqe = false;
				break;
			}
			UniqueDigits.Add(C);
		}
		if (bIsUniqe == false)
		{
			break;;
			
		}
		bCanPlay = true;
		
	}
	while (false);

	return bCanPlay;
}
void AHMGameModeBase::JudgeGame(AHMPlayerController* InChattingPlayerController, int InStrikeCount)
{
	if (3 == InStrikeCount)
	{
		AHMPlayerState* HMPS = InChattingPlayerController -> GetPlayerState<AHMPlayerState>();
		for (const auto& HMPlayerController: AllPlayerControllers)
		{
			if (IsValid(HMPS) == true)
			{
				FString CombinedMessageString = HMPS -> PlayerNameString + TEXT("has won the Game.");
				HMPlayerController -> NotificationText = FText::FromString(CombinedMessageString);
				ResetGame();
			}
		}
	}
	else
	{
		bool bIsDraw = true;
		for (const auto& HMPlayerController: AllPlayerControllers)
		{
			AHMPlayerState* HMPS = InChattingPlayerController -> GetPlayerState<AHMPlayerState>();
			if (IsValid(HMPS) == true)
			{
				if (HMPS -> CurrentGuesssCount < HMPS -> MaxGuessesCount)
				{
					bIsDraw = false;
					break;
				}
			}
		}
		if (true == bIsDraw)
		{
			for (const auto& HMPlayerController: AllPlayerControllers)
			{
				HMPlayerController ->NotificationText = FText::FromString(TEXT("Doro.."));
			}
			ResetGame();
		}
	}
}


FString AHMGameModeBase::JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString )
{
	int32 StrikeCount = 0, BallCount = 0;

	for (int32 i=0; i<3; ++i)
	{
		if (InSecretNumberString[i] == InGuessNumberString[i])
		{
			StrikeCount++;
		}
		else
		{
			FString PlayerGuessChar = FString::Printf(TEXT("%c"), InSecretNumberString[i]);
			if (InSecretNumberString.Contains(PlayerGuessChar))
			{
				BallCount++;
			}
		}
	}
	if (StrikeCount == 0&& BallCount == 3)
	{
		return TEXT("OUT");
		
	}
	return FString :: Printf(TEXT("%dS%dB"), StrikeCount, BallCount);
	
}

void AHMGameModeBase::ResetGame()
{
	SecretNumberString = GenerateSecretNumber();
	for (const auto& HMPlayerController: AllPlayerControllers)
	{
		AHMPlayerState* HMPS = HMPlayerController -> GetPlayerState<AHMPlayerState>();
		if (IsValid(HMPS) == true)
		{
			HMPS -> CurrentGuesssCount = 0;
		}
	}
}