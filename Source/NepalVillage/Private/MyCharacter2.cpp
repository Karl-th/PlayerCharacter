// Player Controller by Jacob Tjernström


#include "MyCharacter2.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AMyCharacter2::AMyCharacter2()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool AMyCharacter2::CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation, int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor) const
{
    static const FName NAME_AILineOfSight = FName(TEXT("TestPawnLineOfSight"));
    FHitResult HitResult;
    auto sockets = GetMesh()->GetAllSocketNames();
    //Here we consider the NeckSocket as the sourceFVectorsocketLocation = 
    FVector socketLocation = GetMesh()->GetSocketLocation("NeckSocket");

    const bool bHitSocket = GetWorld()->LineTraceSingleByObjectType(HitResult, ObserverLocation, socketLocation, FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic)), FCollisionQueryParams(NAME_AILineOfSight, true, IgnoreActor));
    NumberOfLoSChecksPerformed++;
    if (bHitSocket == false || (HitResult.Actor.IsValid() && HitResult.Actor->IsOwnedBy(this)))
    {
        OutSeenLocation = socketLocation;
        OutSightStrength = 1;
        UE_LOG(LogTemp, Warning, TEXT("TRUE"));
        return true;
    }
    const bool bHit = GetWorld()->LineTraceSingleByObjectType(HitResult, ObserverLocation, GetActorLocation(), FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic)), FCollisionQueryParams(NAME_AILineOfSight, true, IgnoreActor));
    NumberOfLoSChecksPerformed++;
    if (bHit == false || (HitResult.Actor.IsValid() && HitResult.Actor->IsOwnedBy(this)))
    {
        OutSeenLocation = GetActorLocation();
        OutSightStrength = 1;
        UE_LOG(LogTemp, Warning, TEXT("TRUE"));
        return true;
    }
    UE_LOG(LogTemp, Warning, TEXT("FALSE"));
    OutSightStrength = 0;
    return false;
}

// Called when the game starts or when spawned
void AMyCharacter2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

