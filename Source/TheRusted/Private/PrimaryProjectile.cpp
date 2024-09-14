// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimaryProjectile.h"

#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
APrimaryProjectile::APrimaryProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("Projectile Collision"));
	SetRootComponent(SphereCollisionComp);
	SphereCollisionComp->SetSphereRadius(20.0f);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->UpdatedComponent = SphereCollisionComp;
	ProjectileMovement->ProjectileGravityScale = 0.05f;

	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	NiagaraComp->SetupAttachment(RootComponent);
	NiagaraComp->SetAutoActivate(false);
	
}

// Called when the game starts or when spawned
void APrimaryProjectile::BeginPlay()
{
	Super::BeginPlay();

	if(NiagaraSystem)
	{
		NiagaraComp->SetAsset(NiagaraSystem);
		NiagaraComp->Activate();
	}
}

// Called every frame
void APrimaryProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

