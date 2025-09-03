#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "HMGameStateBase.generated.h"


UCLASS()
class HMCHATTING_API AHMGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
		
public:
	UFUNCTION(NetMulticast, Unreliable)
	void MulticastRPCBroadcastLoginMessage(const FString& InNameString = FString(TEXT("XXXXXXX")));
};
