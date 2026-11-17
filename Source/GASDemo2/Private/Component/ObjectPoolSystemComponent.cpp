

#include "Component/ObjectPoolSystemComponent.h"
#include "ObjectPoolSystem/ObjectPoolSystem.h"

UObjectPoolSystemComponent::UObjectPoolSystemComponent()
{
	this->PrimaryComponentTick.bCanEverTick = false;

}


void UObjectPoolSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->HasAuthority() == true)
	{
		GetWorld()->GetTimerManager().SetTimer(this->LifetimeLoopingTimerHandle, this, &UObjectPoolSystemComponent::OnLoop, this->LoopingFrequency, true);
		GetWorld()->GetTimerManager().PauseTimer(this->LifetimeLoopingTimerHandle);
	}
}

void UObjectPoolSystemComponent::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	this->ActivationDeLegate.Unbind();
	this->DeactivationDeLegate.Unbind();
	this->LifetimeLoopingDeLegate.Unbind();

	if (GetOwner()->HasAuthority() == true)
	{
		GetWorld()->GetTimerManager().ClearTimer(this->LifetimeTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(this->LifetimeLoopingTimerHandle);
	}

}


void UObjectPoolSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UObjectPoolSystemComponent::ActivatedOwner()
{
	if(this->IsActivated == true|| GetOwner()->HasAuthority() == false) return;
	this->ActivationDeLegate.ExecuteIfBound();
	this->IsActivated = true;
	if (this->LifetimeLoopingDeLegate.IsBound() == true)
	{
		GetWorld()->GetTimerManager().UnPauseTimer(this->LifetimeLoopingTimerHandle);
	}
	if (this->Lifetime <= 0.0f) return;
	GetWorld()->GetTimerManager().ClearTimer(this->LifetimeTimerHandle);
	GetWorld()->GetTimerManager().SetTimer
	(
		this->LifetimeTimerHandle,
		[this]()
		{
			DeactivatedOwner();
		},
		this->Lifetime,
		false
	);

}

void UObjectPoolSystemComponent::DeactivatedOwner()
{
	if (this->IsActivated == false || GetOwner()->HasAuthority() == false) return;

	this->DeactivationDeLegate.ExecuteIfBound();
	this->IsActivated = false;
	if (this->LifetimeLoopingDeLegate.IsBound() == true)
	{
		GetWorld()->GetTimerManager().PauseTimer(this->LifetimeLoopingTimerHandle);
	}
}

void UObjectPoolSystemComponent::OnLoop()
{

	this->LifetimeLoopingDeLegate.ExecuteIfBound();


}

AActor* UObjectPoolSystemComponent::GetActorFromSystem(UClass* ObjectClass, const FString& PoolName, const FTransform& ObjectTransform)
{
	if (GetOwner()->HasAuthority() == false) return nullptr;
	AActor* Object = UObjectPoolSystem::Get(GetOwner()->GetGameInstance())->GetObject(ObjectClass, PoolName, ObjectTransform);
	return Object;
}

void UObjectPoolSystemComponent::ReturnObjectToSystem(const FString& PoolName, AActor* Object)
{
	if (GetOwner()->HasAuthority() == false) return;

	UObjectPoolSystem::Get(GetOwner()->GetGameInstance())->ReturnObject(PoolName,Object);

}

