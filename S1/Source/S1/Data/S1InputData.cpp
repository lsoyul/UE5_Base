#include "Data/S1InputData.h"
#include "S1LogChannels.h"

const UInputAction* US1InputData::FindInputActionByTag(const FGameplayTag& InputTag) const
{
	for (const FS1InputAction& Action : InputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	UE_LOG(LogS1, Error, TEXT("Can't find InputAction for InputTag [%s}"), *InputTag.ToString());

	return nullptr;
}
