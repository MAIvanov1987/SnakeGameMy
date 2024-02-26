// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "SnakeBase.h"
// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (CubeVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();

	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 10.0f;       //Scale our height by a factor of 20

	float DeltaOffsetX = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.X += DeltaOffsetX * 10.0f;       //Scale our height by a factor of 20

	float DeltaRotation = DeltaTime * RotationSpeed;    //Rotate by a number of degrees equal to RotationSpeed each second
	NewRotation.Yaw += DeltaRotation;
	SetActorLocationAndRotation(NewLocation, NewRotation);

	NewLocation.Z += DeltaHeight * FloatSpeed;          //Scale our height by FloatSpeed
	NewLocation.X += DeltaOffsetX * FloatSpeed;
}

void AFood::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)                               // метод, если наступило событие (в голове) то нужно добавить элемент
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		
		{
			Snake->AddSnakeElement();  // добавить 1 элемент к змейке
			
			Destroy();
		}
	}

}
