
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamSuiFederationApi.h"
#include "BeamCoreSettings.h"


void UBeamSuiFederationApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
	RequestTracker = Cast<UBeamRequestTracker>(Collection.InitializeDependency(UBeamRequestTracker::StaticClass()));
	ResponseCache = Cast<UBeamResponseCache>(Collection.InitializeDependency(UBeamResponseCache::StaticClass()));
	MicroserviceName = TEXT("SuiFederation");
}

void UBeamSuiFederationApi::Deinitialize()
{
	Super::Deinitialize();
}


void UBeamSuiFederationApi::BP_GetSuiEnvironmentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, USuiFederationGetSuiEnvironmentRequest* RequestData,
                                                  const FOnSuiFederationGetSuiEnvironmentSuccess& OnSuccess, const FOnSuiFederationGetSuiEnvironmentError& OnError, const FOnSuiFederationGetSuiEnvironmentComplete& OnComplete,
                                                  int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateMicroserviceRequest(OutRequestId, TargetRealm, RetryConfig, RequestData, Prefix);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunBlueprintRequestProcessor<USuiFederationGetSuiEnvironmentRequest, USuiFederationGetSuiEnvironmentResponse, FOnSuiFederationGetSuiEnvironmentSuccess, FOnSuiFederationGetSuiEnvironmentError, FOnSuiFederationGetSuiEnvironmentComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{			
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<USuiFederationGetSuiEnvironmentRequest, USuiFederationGetSuiEnvironmentResponse, FOnSuiFederationGetSuiEnvironmentSuccess, FOnSuiFederationGetSuiEnvironmentError, FOnSuiFederationGetSuiEnvironmentComplete>
			(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId);		
	}	
}

void UBeamSuiFederationApi::CPP_GetSuiEnvironmentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig,
                                               USuiFederationGetSuiEnvironmentRequest* RequestData, const FOnSuiFederationGetSuiEnvironmentFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateMicroserviceRequest(OutRequestId, TargetRealm, RetryConfig, RequestData, Prefix);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunCodeRequestProcessor<USuiFederationGetSuiEnvironmentRequest, USuiFederationGetSuiEnvironmentResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, RequestData, Handler);			
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeCodeRequestProcessor<USuiFederationGetSuiEnvironmentRequest, USuiFederationGetSuiEnvironmentResponse>
			(OutRequestId, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId);	
	}
}



void UBeamSuiFederationApi::BP_WithdrawImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                USuiFederationWithdrawRequest* RequestData, const FOnSuiFederationWithdrawSuccess& OnSuccess, const FOnSuiFederationWithdrawError& OnError, const FOnSuiFederationWithdrawComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateMicroserviceAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData, Prefix);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<USuiFederationWithdrawRequest, UBeamPlainTextResponseBody, FOnSuiFederationWithdrawSuccess, FOnSuiFederationWithdrawError, FOnSuiFederationWithdrawComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<USuiFederationWithdrawRequest, UBeamPlainTextResponseBody, FOnSuiFederationWithdrawSuccess, FOnSuiFederationWithdrawError, FOnSuiFederationWithdrawComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId);	
	}
}

void UBeamSuiFederationApi::CPP_WithdrawImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              USuiFederationWithdrawRequest* RequestData, const FOnSuiFederationWithdrawFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateMicroserviceAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData, Prefix);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<USuiFederationWithdrawRequest, UBeamPlainTextResponseBody>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<USuiFederationWithdrawRequest, UBeamPlainTextResponseBody>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId);	
	}
}




void UBeamSuiFederationApi::CPP_GetSuiEnvironment(USuiFederationGetSuiEnvironmentRequest* Request, const FOnSuiFederationGetSuiEnvironmentFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(USuiFederationGetSuiEnvironmentRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_GetSuiEnvironmentImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), AS_None};
}



void UBeamSuiFederationApi::CPP_Withdraw(const FUserSlot& UserSlot, USuiFederationWithdrawRequest* Request, const FOnSuiFederationWithdrawFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(USuiFederationWithdrawRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_WithdrawImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, AS_None};
}




void UBeamSuiFederationApi::GetSuiEnvironment(USuiFederationGetSuiEnvironmentRequest* Request, const FOnSuiFederationGetSuiEnvironmentSuccess& OnSuccess, const FOnSuiFederationGetSuiEnvironmentError& OnError, const FOnSuiFederationGetSuiEnvironmentComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(USuiFederationGetSuiEnvironmentRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_GetSuiEnvironmentImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), AS_None};
}



void UBeamSuiFederationApi::Withdraw(FUserSlot UserSlot, USuiFederationWithdrawRequest* Request, const FOnSuiFederationWithdrawSuccess& OnSuccess, const FOnSuiFederationWithdrawError& OnError, const FOnSuiFederationWithdrawComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(USuiFederationWithdrawRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_WithdrawImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, AS_None};
}

