// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Interactable.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;  // размер откладываемых элементов змейки поумолчанию
	MovementSpeed = 10.f; // скорость движения змейки поумолчанию
	LastMoveDirection = EMovementDirection::DOWN; // направление движение змейки поумолчанию
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed); // вызываем метод установки частоты кадра в секундах = movementspeed = elementsize
	AddSnakeElement(5);   // вызываем метод добавления элементов к змейке
	//ReturnActorLocation();
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();  // вызов метода движения
}

void ASnakeBase::AddSnakeElement(int ElementsNum) // определение метода добавления новых элементов 
{
	
	for (int i = 0; i < ElementsNum; ++i)
	{
		FVector NewLocation((SnakeElements.Num() * ElementSize),0,0);
	
		//NewLocation.X = (NewLocation.X * ElementSize);
		//NewLocation.Y = 0;
		//NewLocation.Z = 20;
		//auto LastElemLoc = SnakeElements[i];
		//FVector Location = LastElemLoc->GetActorLocation();
		//FVector NewLoc = FVector(Location.X, Location.Y, Location.Z);
		//LastElemLoc->SetActorLocation(NewLoc);
		FTransform NewTransform(NewLocation); // сохраняем новый отложенный элемент в переменной
		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform); // спаун новых элементов с добавлением в массив
		NewSnakeElem->SnakeOwner = this; // присоединение владельца змейки к элементу змейки
		
		int32 ElemIndex = SnakeElements.Add(NewSnakeElem);
		
		if (ElemIndex == 0)
		{
			NewSnakeElem->SetFirstElementType();

		}
		else
		{ // отключаем коллизию столкновения с хвостом
			NewSnakeElem->SetActorEnableCollision(ECollisionEnabled::NoCollision);
		}

	}

}



void ASnakeBase::Move() // метод перемещения змейки
{
	FVector MovementVector(ForceInitToZero); // сформируем вектор движения (спаун змейки по оси z = координате 0)

	switch (LastMoveDirection)
	{
	case EMovementDirection::UP:
		MovementVector.X += ElementSize;
		break;
	case EMovementDirection::DOWN:
		MovementVector.X -= ElementSize;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y += ElementSize;
		break;
	case EMovementDirection::RIGHT:
		MovementVector.Y -= ElementSize;
		break;
	}

	//AddActorWorldOffset(MovementVector);  // добавить перемещение(смещение) актера
	SnakeElements[0]->ToggleCollision();    // добавим метод переключения коллизий на нулевой элемент
	for (int i = SnakeElements.Num() - 1; i > 0; i--) // индекс i = последнему элементу массива,для смещения всех элементов змейки к её голове
	{
		auto CurrentElement = SnakeElements[i]; // получение текущего элемента
		auto PrevElement = SnakeElements[i - 1];  // предыдущий элемент
		FVector PrevLocation = PrevElement->GetActorLocation(); //получить местоположение текущего элемента в пространстве
		CurrentElement->SetActorLocation(PrevLocation); // сместить текущий элемент в место предыдущего
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector); // перемещение головы на movementvector отдельно от цикла
	SnakeElements[0]->ToggleCollision(); // включаем коллизию
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other)
{
	if (IsValid(OverlappedElement))
	{
		int32 ElemIndex;
		SnakeElements.Find(OverlappedElement, ElemIndex);
		bool bIsFirst = ElemIndex == 0;  // голова змейки под индексом 0
		IInteractable* InteractableInterface = Cast<IInteractable>(Other);
		if (InteractableInterface)
		{
			InteractableInterface->Interact(this, bIsFirst); // сообщаем змейке о первом элементе - голова
		}
	}
}

void ASnakeBase::ReturnActorLocation()
{

}




