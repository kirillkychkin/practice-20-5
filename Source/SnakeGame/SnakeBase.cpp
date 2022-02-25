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

	SetActorTickInterval(MovementSpeed);

	AddSnakeElement(4);
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; ++i)
	{
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);
		FTransform NewTransform = FTransform(NewLocation);
		ASnakeElementBase* NewSnakeElement = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		//NewSnakeElement->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		SnakeElements.Add(NewSnakeElement);
	}
}

void ASnakeBase::Move()
{
	FVector MovementVector(ForceInitToZero);
	float MovementChange = ElementSize;

	switch (LastMoveDirection)
	{
		case EMovementDirection::UP:
			MovementVector.X += MovementChange;
			break;
		case EMovementDirection::DOWN:
			MovementVector.X -= MovementChange;
			break;
		case EMovementDirection::LEFT:
			MovementVector.Y += MovementChange;
			break;
		case EMovementDirection::RIGHT:
			MovementVector.Y -= MovementChange;
			break;
	}

	//AddActorWorldOffset(MovementVector);
	for (int i = SnakeElements.Num() - 1; i > 0; --i)
	{
		auto CurrentElem = SnakeElements[i];
		auto PreviousElement = SnakeElements[i - 1];
		FVector PreviousLocation = PreviousElement->GetActorLocation();
		CurrentElem->SetActorLocation(PreviousLocation);
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
}

