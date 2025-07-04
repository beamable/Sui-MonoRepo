
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/RealmConfigSaveRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PutConfigRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutConfigRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	URealmConfigSaveRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutConfigRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make PutConfig",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutConfigRequest* Make(TMap<FString, FString> _Config, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutConfigSuccess, FBeamRequestContext, Context, UPutConfigRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutConfigError, FBeamRequestContext, Context, UPutConfigRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutConfigComplete, FBeamRequestContext, Context, UPutConfigRequest*, Request);

using FPutConfigFullResponse = FBeamFullResponse<UPutConfigRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutConfigFullResponse, FPutConfigFullResponse);
