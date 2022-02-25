// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	MovementSpeed = 10.f;
	LastMoveDirection = EMovementDirection::LEFT;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	AddSnakeElement(4);
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; ++i)
	{
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);
		FTransform NewTransform = FTransform(NewLocation);
		ASnakeElementBase* NewSnakeElement = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		NewSnakeElement->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		SnakeElements.Add(NewSnakeElement);
	}
}

void ASnakeBase::Move(float DeltaTime)
{
	FVector MovementVector;
	float MovementDelta = MovementSpeed * DeltaTime;

	switch (LastMoveDirection)
	{
		case EMovementDirection::UP:
			MovementVector.X += MovementDelta;
			break;
		case EMovementDirection::DOWN:
			MovementVector.X -= MovementDelta;
			break;
		case EMovementDirection::LEFT:
			MovementVector.Y += MovementDelta;
			break;
		case EMovementDirection::RIGHT:
			MovementVector.Y -= MovementDelta;
			break;
	}

	AddActorWorldOffset(MovementVector);
}

