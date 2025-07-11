
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "UnrealSuiSampleMicroserviceClients/Public/AutoGen/WithdrawRequestArgs.h"
#include "Serialization/BeamPlainTextResponseBody.h"

#include "SuiFederationWithdrawRequest.generated.h"

UCLASS(BlueprintType)
class UNREALSUISAMPLEMICROSERVICECLIENTS_API USuiFederationWithdrawRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UWithdrawRequestArgs* Body = {};

	// Beam Base Request Declaration
	USuiFederationWithdrawRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|SuiFederation|Utils|Make/Break", DisplayName="Make SuiFederationWithdraw",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static USuiFederationWithdrawRequest* Make(FString _ContentId, int64 _Amount, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnSuiFederationWithdrawSuccess, FBeamRequestContext, Context, USuiFederationWithdrawRequest*, Request, UBeamPlainTextResponseBody*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnSuiFederationWithdrawError, FBeamRequestContext, Context, USuiFederationWithdrawRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnSuiFederationWithdrawComplete, FBeamRequestContext, Context, USuiFederationWithdrawRequest*, Request);

using FSuiFederationWithdrawFullResponse = FBeamFullResponse<USuiFederationWithdrawRequest*, UBeamPlainTextResponseBody*>;
DECLARE_DELEGATE_OneParam(FOnSuiFederationWithdrawFullResponse, FSuiFederationWithdrawFullResponse);
