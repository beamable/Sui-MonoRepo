
#include "BeamableCore/Public/AutoGen/SubSystems/Player/PutPresenceRequest.h"

void UPutPresenceRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("PUT");
}

void UPutPresenceRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/players/{playerId}/presence");
	Route = Route.Replace(TEXT("{playerId}"), *PlayerId);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPutPresenceRequest::BuildBody(FString& BodyString) const
{
	
}

UPutPresenceRequest* UPutPresenceRequest::Make(FString _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPutPresenceRequest* Req = NewObject<UPutPresenceRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->PlayerId = _PlayerId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
