// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Tanker.h"
#include "ShieldComponent.h"
#include "Components/ArrowComponent.h"
#include "Projectile_Base.h"
#include "Item.h"

AEnemy_Tanker::AEnemy_Tanker()
{
	PrimaryActorTick.bCanEverTick = true;
	SetSkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Enemy/Tanker/Animation/SCIFI_ROBOT_IK_SK1.SCIFI_ROBOT_IK_SK1'"));

	FireArrow= CreateDefaultSubobject<UArrowComponent>(TEXT("FireArrow"));
	FireArrow->SetupAttachment(GetMesh(), FName("FireArrow"));
	FireArrow->SetRelativeLocationAndRotation(FVector(0.0f, 3.0f, 160.0f), FRotator(0.0f, 90.0f, 0.0f));

	dropItemID = 2;
}

void AEnemy_Tanker::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy_Tanker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy_Tanker::Die()
{
	bIsDead = true;
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);

	if (ItemDrop)
	{
		FTransform _transform = GetActorTransform();
		GetWorld()->SpawnActor<AItem>(ItemDrop, _transform);
	}

	OnDieSetState();
}

float AEnemy_Tanker::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ret = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	MontagePlay(AM_HitMontage);
	currentHP -= Damage;
	if (currentHP <= 0)
	{
		Die();
	}
	return ret + Damage;
}

void AEnemy_Tanker::SpawnBullet()
{
	FTransform _transform = FireArrow->GetComponentTransform();
	GetWorld()->SpawnActor<AProjectile_Base>(Bullet, _transform);
}
