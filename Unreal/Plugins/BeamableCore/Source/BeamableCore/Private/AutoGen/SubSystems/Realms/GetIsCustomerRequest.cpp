
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetIsCustomerRequest.h"

void UGetIsCustomerRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetIsCustomerRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/is-customer");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetIsCustomerRequest::BuildBody(FString& BodyString) const
{
	
}

UGetIsCustomerRequest* UGetIsCustomerRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetIsCustomerRequest* Req = NewObject<UGetIsCustomerRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
