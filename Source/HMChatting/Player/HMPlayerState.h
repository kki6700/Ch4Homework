#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "HMPlayerState.generated.h"


UCLASS()
class HMCHATTING_API AHMPlayerState : public APlayerState
{
	GENERATED_BODY()
public:

	AHMPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	FString GetPlayerInfoString();

	UPROPERTY(Replicated)
	FString PlayerNameString;

	UPROPERTY(Replicated)
	int32 CurrentGuesssCount;

	UPROPERTY(Replicated)
	int32 MaxGuessesCount;
};
