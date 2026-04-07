// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

//DEFINE_LOG_CATEGORY(LogSparta);

// Sets default values
AItem::AItem()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
	// '/Game/Resources/Props/SM_Chair.SM_Chair'
	// '/Game/Resources/Materials/M_Potion_Poison.M_Potion_Poison'
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Chair.SM_Chair"));
	//
	//if (MeshAsset.Succeeded())
	//{
	//	StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	//}
	//
	//static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Potion_Poison.M_Potion_Poison"));
	//if (MaterialAsset.Succeeded()) 
	//{
	//	StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	//}

	PrimaryActorTick.bCanEverTick = true;

	RotationSpeed = 90.0f;
}

void AItem::BeginPlay() 
{
	Super::BeginPlay();

	// BeginPlay 호출 시점을 로그로 확인
	//UE_LOG(LogTemp, Warning, TEXT("My Item appears!!"));
	//UE_LOG(LogSparta, Error, TEXT("My Log!!"));

	//SetActorLocation(FVector(300.0f, 200.0f, 100.0f));
	//SetActorRotation(FRotator(0.0f, 90.f, 0.0f)); //pitch,yaw,roll -> y,z,x
	//SetActorScale3D(FVector(2.0f, 1.0f, 1.0f));

	//FVector NewLocation(300.0f, 200.0f, 100.0f);
	//FRotator NewRotation(0.0f, 90.f, 0.0f);
	//FVector NewScale(2.0f);
	//
	//FTransform NewTransform(NewRotation, NewLocation, NewScale);//Rotation,Location,Scale
	//SetActorTransform(NewTransform);

	OnItemPickedUp();

}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	}
}

void AItem::ResetActorPosition()
{
	SetActorLocation(FVector::ZeroVector);
}

float AItem::GetRotationSpeed() const
{
	return RotationSpeed;
}