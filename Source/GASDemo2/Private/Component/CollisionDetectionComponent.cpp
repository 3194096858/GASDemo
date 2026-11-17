

#include "Component/CollisionDetectionComponent.h"


#include "Kismet/KismetSystemLibrary.h"


UCollisionDetectionComponent::UCollisionDetectionComponent()
{

}


void UCollisionDetectionComponent::BeginPlay()
{
	Super::BeginPlay();


}


void UCollisionDetectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}



TArray<FHitResult> UCollisionDetectionComponent::GetAllHitResult()
{
	return this->HitResultArray;
}

FHitResult UCollisionDetectionComponent::GetFirstHitResult()
{
	if (this->HitResultArray.Num() == 0)
	{
		return FHitResult();
	}
	return this->HitResultArray[0];
}


int32 UCollisionDetectionComponent::GetHitResultNumber()
{
	return this->HitResultArray.Num();
}


void UCollisionDetectionComponent::RemoveAllHitResult()
{
	if (this->HitResultArray.Num() == 0)
	{
		return;
	}
	this->HitResultArray.Empty();
}


void UCollisionDetectionComponent::RemoveAllIgnoredActor()
{
	this->IgnoredActorArray.Empty();

}

void UCollisionDetectionComponent::AddIgnoredActor(AActor* Actor)
{
	//if(this->IgnoredActorArray.Contains(Actor) == true);
	this->IgnoredActorArray.AddUnique(Actor);
}



void UCollisionDetectionComponent::RemoveIgnoredActor(AActor* Actor)
{
	this->IgnoredActorArray.Remove(Actor);


}

TArray<AActor*> UCollisionDetectionComponent::GetAllIgnoredActor()
{
	return this->IgnoredActorArray;
}

void UCollisionDetectionComponent::LineTrace(const FVector& StartLocation, const FVector& EndLocation, const FString& ProfileName, bool IsIgnoreSelf)
{
	//TArray<AActor*> IgnoreActorArray;
	EDrawDebugTrace::Type DrawDebugTrace = EDrawDebugTrace::None;
	if (this->IsDebug == true)
	{
		DrawDebugTrace = EDrawDebugTrace::ForDuration;
	}
	RemoveAllHitResult();
	UKismetSystemLibrary::LineTraceMultiByProfile(GetOwner(), StartLocation, EndLocation, FName(ProfileName), false, this->IgnoredActorArray, DrawDebugTrace, this->HitResultArray, IsIgnoreSelf);




}


void UCollisionDetectionComponent::SphereTrace(const FVector& StartLocation, const FVector& EndLocation, float Radius, const FString& ProfileName, bool IsIgnoreSelf)
{
	EDrawDebugTrace::Type DrawDebugTrace = EDrawDebugTrace::None;
	if (this->IsDebug == true)
	{
		DrawDebugTrace = EDrawDebugTrace::ForDuration;
	}
	RemoveAllHitResult();
	UKismetSystemLibrary::SphereTraceMultiByProfile(GetOwner(), StartLocation, EndLocation, Radius, FName(ProfileName), false, this->IgnoredActorArray, DrawDebugTrace, this->HitResultArray, IsIgnoreSelf);




}


void UCollisionDetectionComponent::BoxTrace(const FVector& StartLocation, const FVector& EndLocation, const FVector& HalfSize, const FRotator& Orientation, const FString& ProfileName, bool IsIgnoreSelf)
{
	EDrawDebugTrace::Type DrawDebugTrace = EDrawDebugTrace::None;
	if (this->IsDebug == true)
	{
		DrawDebugTrace = EDrawDebugTrace::ForDuration;
	}


	RemoveAllHitResult();
	UKismetSystemLibrary::BoxTraceMultiByProfile(GetOwner(), StartLocation, EndLocation, HalfSize, Orientation, FName(ProfileName), false, this->IgnoredActorArray, DrawDebugTrace, this->HitResultArray, IsIgnoreSelf);




}


void UCollisionDetectionComponent::CapsuleTrace(const FVector& StartLocation, const FVector& EndLocation, float Radius, float HalfHeight, const FString& ProfileName, bool IsIgnoreSelf)
{
	EDrawDebugTrace::Type DrawDebugTrace = EDrawDebugTrace::None;
	if (this->IsDebug == true)
	{
		DrawDebugTrace = EDrawDebugTrace::ForDuration;
	}
	RemoveAllHitResult();
	UKismetSystemLibrary::CapsuleTraceMultiByProfile(GetOwner(), StartLocation, EndLocation, Radius, HalfHeight, FName(ProfileName), false, this->IgnoredActorArray, DrawDebugTrace, this->HitResultArray, IsIgnoreSelf);


}

