// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Grim_Primary.h"

#include "Enemy_Base.h"
#include "Player_Base.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void AProjectile_Grim_Primary::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), VFX_Spawn, GetActorLocation(), GetActorRotation());
}

void AProjectile_Grim_Primary::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(!bHit)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), VFX_NoHit, GetActorLocation(), GetActorRotation());
	}
}

void AProjectile_Grim_Primary::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnComponentHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	if(OtherActor == nullptr)
    		return;
    	
    	if(OtherComp == nullptr)
    		return;
    	
    	if(OtherActor->IsA(AEnemy_Base::StaticClass()))
    		return;
    
    	bHit = true;
    	
    	if(OtherActor->IsA(APlayer_Base::StaticClass()))
    	{
    		UGameplayStatics::ApplyDamage(OtherActor, 10.0f, GetInstigatorController(), this, UDamageType::StaticClass());
    		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), VFX_HitCharacter, Hit.ImpactPoint, UKismetMathLibrary::MakeRotFromZ(Hit.ImpactNormal));
    	}
    	else
    	{
    		UGameplayStatics::ApplyDamage(OtherActor, 10.0f, GetInstigatorController(), this, UDamageType::StaticClass());
    		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), VFX_HitWorld, Hit.ImpactPoint, UKismetMathLibrary::MakeRotFromZ(Hit.ImpactNormal));
    	}
    	
    	Destroy();
}
