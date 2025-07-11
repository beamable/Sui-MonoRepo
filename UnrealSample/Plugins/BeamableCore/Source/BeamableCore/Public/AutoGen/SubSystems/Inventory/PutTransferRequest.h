
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamGamerTag.h"
#include "BeamableCore/Public/AutoGen/TransferRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PutTransferRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutTransferRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FBeamGamerTag ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UTransferRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutTransferRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make PutTransfer",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Transaction,_Currencies,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutTransferRequest* Make(FBeamGamerTag _ObjectId, FBeamGamerTag _RecipientPlayer, FOptionalString _Transaction, FOptionalMapOfInt64 _Currencies, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutTransferSuccess, FBeamRequestContext, Context, UPutTransferRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutTransferError, FBeamRequestContext, Context, UPutTransferRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutTransferComplete, FBeamRequestContext, Context, UPutTransferRequest*, Request);

using FPutTransferFullResponse = FBeamFullResponse<UPutTransferRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutTransferFullResponse, FPutTransferFullResponse);
