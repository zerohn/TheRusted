// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character_Base.h"
#include "InputActionValue.h"
#include "KYH_CharacterStatus.h"
#include "Player_Base.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class THERUSTED_API APlayer_Base : public ACharacter_Base
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer_Base();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* CameraComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArmComp;

	// Input
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveIA;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* LookUpIA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	bool bLookUpInvert = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* TurnIA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* JumpIA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* AttackIA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* UltimateIA;


	void Move(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void InputJump(const FInputActionValue& Value);
	void InputAttack(const FInputActionValue& Value);
	void InputUltimate(const FInputActionValue& Value);

	FVector MoveDirection;

	// Attack Animation
	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* AttackAnimMontage;

	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* StrongAttackAnimMontage;

	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* HitAnimMontage;

	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* UltimateAnimMontage;

	bool bCanStrongAttack;

	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void Attack();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void StrongAttack();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void Ultimate();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats")
	FBasicStatus BasicStatus;

	// Util
	FTransform Calc_AttackTransform(FName socketName);


	
};
