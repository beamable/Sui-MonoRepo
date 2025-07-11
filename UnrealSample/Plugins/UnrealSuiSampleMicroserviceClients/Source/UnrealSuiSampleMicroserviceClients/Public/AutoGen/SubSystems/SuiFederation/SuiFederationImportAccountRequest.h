
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "UnrealSuiSampleMicroserviceClients/Public/AutoGen/ImportAccountRequestArgs.h"
#include "UnrealSuiSampleMicroserviceClients/Public/AutoGen/SuiFederationImportAccountResponse.h"

#include "SuiFederationImportAccountRequest.generated.h"

UCLASS(BlueprintType)
class UNREALSUISAMPLEMICROSERVICECLIENTS_API USuiFederationImportAccountRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UImportAccountRequestArgs* Body = {};

	// Beam Base Request Declaration
	USuiFederationImportAccountRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|SuiFederation|Utils|Make/Break", DisplayName="Make SuiFederationImportAccount",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static USuiFederationImportAccountRequest* Make(FString _Id, FString _PrivateKey, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnSuiFederationImportAccountSuccess, FBeamRequestContext, Context, USuiFederationImportAccountRequest*, Request, USuiFederationImportAccountResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnSuiFederationImportAccountError, FBeamRequestContext, Context, USuiFederationImportAccountRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnSuiFederationImportAccountComplete, FBeamRequestContext, Context, USuiFederationImportAccountRequest*, Request);

using FSuiFederationImportAccountFullResponse = FBeamFullResponse<USuiFederationImportAccountRequest*, USuiFederationImportAccountResponse*>;
DECLARE_DELEGATE_OneParam(FOnSuiFederationImportAccountFullResponse, FSuiFederationImportAccountFullResponse);
