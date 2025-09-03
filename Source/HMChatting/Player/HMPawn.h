#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HMpawn.generated.h"


UCLASS()
class HMCHATTING_API AHMPawn: public  APawn
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;	
	
};
