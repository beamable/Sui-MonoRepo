#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalEntitlementClaimWindow.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfString.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "EntitlementGenerator.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UEntitlementGenerator : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol", Category="Beam")
	FString Symbol = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Action", Category="Beam")
	FString Action = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Quantity", Category="Beam")
	FOptionalInt32 Quantity = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Claim Window", Category="Beam")
	FOptionalEntitlementClaimWindow ClaimWindow = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Specialization", Category="Beam")
	FOptionalString Specialization = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Params", Category="Beam")
	FOptionalMapOfString Params = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};