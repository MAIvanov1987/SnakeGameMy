// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "SnakeElementBase.generated.h"

class UStaticMeshComponent;  // компонент статик меш
class ASnakeBase;

UCLASS()
class SNAKEGAME_API ASnakeElementBase : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeElementBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) 
	UStaticMeshComponent* MeshComponent;  // переменная с указателем на класс

	UPROPERTY()
	ASnakeBase* SnakeOwner;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
	void SetFirstElementType();
	void SetFirstElementType_Implementation();
	

	virtual void Interact(AActor* Interactor, bool bIsHead) override;

	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodeIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult); // метод пересечения компонентов

	UFUNCTION()
	void ToggleCollision(); // метод переключения коллизии между querryonly и no collision
};
