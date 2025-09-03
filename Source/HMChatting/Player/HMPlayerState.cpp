#include "HMPlayerState.h"
#include "Net/UnrealNetwork.h"


AHMPlayerState::AHMPlayerState():PlayerNameString(TEXT("NONE")),CurrentGuesssCount(0),MaxGuessesCount(3)
{
	bReplicates = true;
}


void AHMPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, PlayerNameString);
	DOREPLIFETIME(ThisClass, CurrentGuesssCount);
	DOREPLIFETIME(ThisClass, MaxGuessesCount);
}

FString AHMPlayerState::GetPlayerInfoString()
{
	FString PlayerInfoString = PlayerNameString + TEXT("(") + FString::FromInt(CurrentGuesssCount) + TEXT("/") + FString::FromInt(MaxGuessesCount) + TEXT(")");
	return PlayerInfoString;
}


