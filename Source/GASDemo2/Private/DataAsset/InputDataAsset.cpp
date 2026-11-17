

#include "DataAsset/InputDataAsset.h"

UInputAction* UInputDataAsset::GetInputAction(const FGameplayTag& Tag)
{
    UInputAction** InputAction = this->InputMap.Find(Tag);
    if (InputAction == nullptr) return nullptr;
    return *InputAction;
}
