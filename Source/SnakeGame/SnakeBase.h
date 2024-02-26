// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeBase.generated.h"

class ASnakeElementBase;

UENUM()   // задание направления движения
enum class EMovementDirection // класс системы передвижения
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

UCLASS()
class SNAKEGAME_API ASnakeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeBase();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeElementBase> SnakeElementClass; // переменная snakeelementclass класса snakeelementbase

	UPROPERTY(EditDefaultsOnly)
	float ElementSize;               // переменная для растяжения змейки в длинну, т.е. отвечает за размер элемента
	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed;        // параметр отвечающий за скорость перемещения змейки

	UPROPERTY()
	TArray<ASnakeElementBase*> SnakeElements; // массив для инициализации змейки и создания элементов змейки

	UPROPERTY()
	EMovementDirection LastMoveDirection;  // реализация метода движения
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void AddSnakeElement(int ElementsNum = 1); // метод добавления к змейке новых элементов
	UFUNCTION()
	
	void Move(); // метод движения
	UFUNCTION()
	void SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other);//событие что наш блок змейки сколизился с чем-то

	void ReturnActorLocation();

	
};
