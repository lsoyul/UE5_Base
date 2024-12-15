#include "S1GameInstance.h"
#include "S1AssetManager.h"

US1GameInstance::US1GameInstance(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void US1GameInstance::Init()
{
	Super::Init();

	US1AssetManager::Initialize();
}

void US1GameInstance::Shutdown()
{
	Super::Shutdown();
}
