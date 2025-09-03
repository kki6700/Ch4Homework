#include "HMPawn.h"
#include "HMChatting.h"


void AHMPawn::BeginPlay()
{
	Super::BeginPlay();

	FString NetRoleString = HMChatFuntionKibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("HMPawn::BeginPlay() %s [%s]"), *HMChatFuntionKibrary::GetRoleString(this),*NetRoleString);
	HMChatFuntionKibrary::MyPrintString(this,CombinedString, 10.f);
	
}


void AHMPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	FString NetRoleString = HMChatFuntionKibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("HMPawn::PossessedBy() %s [%s]"), *HMChatFuntionKibrary::GetRoleString(this),*NetRoleString);
	HMChatFuntionKibrary::MyPrintString(this,CombinedString, 10.f);
}
