// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeElementBase.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "SnakeBase.h"

// Sets default values
ASnakeElementBase::ASnakeElementBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent")); //присвоить переменной создание статик меша
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly); //открытие коллизии компонента для того чтобы со змейкой что-то происходило после столкновения с этим компонентом 
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap); // открытие коллизии по всем каналам на подсчет пересечений overlap
}

// Called when the game starts or when spawned
void ASnakeElementBase::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ASnakeElementBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASnakeElementBase::SetFirstElementType_Implementation()
{
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ASnakeElementBase::HandleBeginOverlap); //сообщение о том, что произошло пересечение overlap
}

void ASnakeElementBase::Interact(AActor* Interactor, bool bIsHead) // реализация внутри змейки, элементов после коллизии
{
	auto Snake = Cast<ASnakeBase>(Interactor); //получаем скастованный указатель на змейку
	
	if (IsValid(Snake))
	{
		
		Snake->Destroy(); // отправляем событие-уничтожить на змейку
		
		
	}
}

void ASnakeElementBase::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodeIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (IsValid(SnakeOwner))
	{
		SnakeOwner->SnakeElementOverlap(this, OtherActor); 
	}
	
}

void ASnakeElementBase::ToggleCollision() // реализация метода переключения коллизий
{
	if (MeshComponent->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
	{
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	}
}

