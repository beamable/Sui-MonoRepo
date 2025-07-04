
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PostCustomerVerifyRequest.h"

void UPostCustomerVerifyRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostCustomerVerifyRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/customer/verify");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostCustomerVerifyRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostCustomerVerifyRequest* UPostCustomerVerifyRequest::Make(FString _ProjectName, FString _Email, FString _Password, FOptionalBool _bHierarchy, FOptionalString _CustomerName, FOptionalString _Alias, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostCustomerVerifyRequest* Req = NewObject<UPostCustomerVerifyRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UNewCustomerRequestBody>(Req);
	Req->Body->ProjectName = _ProjectName;
	Req->Body->Email = _Email;
	Req->Body->Password = _Password;
	Req->Body->bHierarchy = _bHierarchy;
	Req->Body->CustomerName = _CustomerName;
	Req->Body->Alias = _Alias;
	

	return Req;
}
