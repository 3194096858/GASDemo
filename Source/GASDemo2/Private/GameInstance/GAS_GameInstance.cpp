

#include "GameInstance/GAS_GameInstance.h"
#include "AssetManager/GAS_AssetManager.h"




void UGAS_GameInstance::Init()
{
	Super::Init();
	if (this->AssetManagerClass == nullptr) return;
	this->AssetManager = NewObject<UGAS_AssetManager>(this,this->AssetManagerClass);

}

void UGAS_GameInstance::OnStart()
{
	Super::OnStart();



}
