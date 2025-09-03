#include "HMGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/HMPlayerController.h"

void AHMGameStateBase::MulticastRPCBroadcastLoginMessage_Implementation(const FString& InNameString)
{
	if (HasAuthority() == false)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
		if (IsValid(PC) == true)
		{
			AHMPlayerController* HMPC = Cast<AHMPlayerController>(PC);
			if (IsValid(HMPC) == true)
			{
				FString NotificationString = InNameString + TEXT(" has joined the Game.");
				HMPC -> PrintChatMessageString(NotificationString);
			}
		}
	}
}
