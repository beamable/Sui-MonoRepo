#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalGamerTagAssociation.h"

#include "OptionalGamerTagAssociationLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalGamerTagAssociationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalGamerTagAssociation struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Optionals", meta=(DisplayName="Make Optional GamerTagAssociation", NativeMakeFunc))
	static FOptionalGamerTagAssociation MakeOptional(UGamerTagAssociation* Value);

	/**
	 * @brief Converts an UGamerTagAssociation* into an FOptionalGamerTagAssociation automatically.
	 * @param Value The UGamerTagAssociation* to convert.
	 * @return An optional with the GamerTagAssociation set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Optionals", meta = (DisplayName="GamerTagAssociation To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalGamerTagAssociation Conv_OptionalFromValue(UGamerTagAssociation* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Accounts|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalGamerTagAssociation& Optional, UGamerTagAssociation*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Optionals", meta=(DisplayName="Get Optional's GamerTagAssociation Value"))
	static UGamerTagAssociation* GetOptionalValue(const FOptionalGamerTagAssociation& Optional, UGamerTagAssociation* DefaultValue, bool& WasSet);

	
};
