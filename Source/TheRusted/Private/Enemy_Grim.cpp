// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Grim.h"

#include "Projectile_Base.h"
#include "Components/CapsuleComponent.h"

AEnemy_Grim::AEnemy_Grim()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(130.0f);
	GetCapsuleComponent()->SetCapsuleRadius(60);
	SetSkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGRIMexe/Characters/Heroes/GRIM/Skins/Tier1_5/Wasteland/Meshes/GRIMWasteland.GRIMWasteland'"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -130.0f), FRotator(0.0f, -90.0f, 0.0f));
}

void AEnemy_Grim::BeginPlay()
{
	Super::BeginPlay();

	if (Projectiles.Num() > 0) {
		SelectedProjectile = Projectiles[0];
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Projectiles is Empty"));
	}

	MontagePlay(AM_LevelStart);
}

void AEnemy_Grim::Attack_Primary()
{
	if (bCanAttack) {
		//bCanAttack = false;
		SelectedProjectile = Projectiles[0];
		MontagePlay(AM_Attack_Primary);
	}
}

void AEnemy_Grim::Attack_Strong()
{
	if (bCanAttack) {
		bCanAttack = false;
		bCanMove = false;
		SelectedProjectile = Projectiles[1];
		MontagePlay(AM_Attack_Strong);
	}
}

void AEnemy_Grim::Attack_Ultimate()
{
	if (bCanAttack) {
		bCanAttack = false;
		bCanMove = false;
		SelectedProjectile = Projectiles[2];
		MontagePlay(AM_Attack_Ultimate);
	}
}

void AEnemy_Grim::Attack()
{
	FTransform FireTransform = Calc_AttackTransform(FName("WeaponAttachPointR"));
	DrawDebugDirectionalArrow(GetWorld(), FireTransform.GetLocation(), FireTransform.GetLocation() + FireTransform.GetRotation().Vector() * 100.0f, 50.0f, FColor::Red, false, 5.0f);
	
	GetWorld()->SpawnActor<AProjectile_Base>(SelectedProjectile, FireTransform);
}
