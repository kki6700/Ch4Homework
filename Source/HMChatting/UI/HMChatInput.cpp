#include "HMChatInput.h"
#include "Components/EditableTextBox.h"
#include "Player/HMPlayerController.h"

void UHMChatInput::NativeConstruct()
{
	Super::NativeConstruct();
	if (EditableTextBox_ChatInput -> OnTextCommitted.IsAlreadyBound(this, &ThisClass::UHMChatInput::OnChatInputTextCommitted) == false)
	{
		EditableTextBox_ChatInput-> OnTextCommitted.AddDynamic(this,&ThisClass::OnChatInputTextCommitted);
		
	}
}

void UHMChatInput::NativeDestruct()
{
	Super::NativeDestruct();

	if (EditableTextBox_ChatInput -> OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted)== true)
	{
		EditableTextBox_ChatInput -> OnTextCommitted.RemoveDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UHMChatInput::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		APlayerController* OwningPlayerController = GetOwningPlayer();
		if (IsValid(OwningPlayerController)==true)
		{
			AHMPlayerController* OwningHMPlayerController = Cast<AHMPlayerController>(OwningPlayerController);
			if (IsValid(OwningPlayerController) == true)
			{
				OwningHMPlayerController-> SetChatMessageString(Text.ToString());
				EditableTextBox_ChatInput-> SetText(FText());
			}
		}	
	}
}