// Fill out your copyright notice in the Description page of Project Settings.
// статичная камера
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawnBase.generated.h"

class UCameraComponent;  // класс компонент камеры
class ASnakeBase;        // класс змейки наследованный от актера

UCLASS()
class SNAKEGAME_API APlayerPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawnBase();

	UPROPERTY(BlueprintReadWrite)  // читать и править в блупринтах
	UCameraComponent* PawnCamera;  // компонент камеры с указателем на павнкамеру

	UPROPERTY(BlueprintReadWrite)
	ASnakeBase* SnakeActor;        // блупринтовая змея наследованная от класса ASnakeBase

	UPROPERTY(EditDefaultsOnly)    // позволяет редактировать переменную только в настройках поумолчанию
	TSubclassOf<ASnakeBase> SnakeActorClass; 
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CreateSnakeActor(); // метод создающий актера змею

	UFUNCTION()
	void HandlePlayerVerticalInput(float value);
	UFUNCTION()
	void HandlePlayerHorizontalInput(float value);
};
