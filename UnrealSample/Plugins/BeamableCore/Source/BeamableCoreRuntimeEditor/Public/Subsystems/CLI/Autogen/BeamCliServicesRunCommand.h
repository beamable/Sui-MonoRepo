#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliServicesRunCommand.generated.h"


UCLASS(BlueprintType)
class UBeamCliServicesRunStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Success = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FailureReason = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Success"), Success, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("FailureReason"), FailureReason, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Success"), Success, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("FailureReason"), FailureReason, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Success")), Success);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("FailureReason")), FailureReason);	
	}
};


UCLASS(BlueprintType)
class UBeamCliServicesRunLocalProgressStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BeamoId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double LocalDeployProgress = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("BeamoId"), BeamoId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("LocalDeployProgress"), LocalDeployProgress, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("BeamoId"), BeamoId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("LocalDeployProgress"), LocalDeployProgress, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("BeamoId")), BeamoId);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("LocalDeployProgress")), LocalDeployProgress);	
	}
};


/**
 Description:
  Run services locally in Docker. Will fail if no docker instance is running in the local machine

Usage:
  Beamable.Tools services run [options]

Options:
  --ids <ids>                            The ids for the services you wish to deploy. Ignoring this option deploys all services
  -fcpu, --force-amd-cpu-arch            Force the services to run with amd64 CPU architecture, useful when deploying from computers with ARM architecture [default: False]
  -k, --keep-containers                  Automatically remove service containers after they exit [default: False]
  --dryrun                               [DEPRECATED] Run as much of the command as possible without making any network calls
  --cid <cid>                            CID (CustomerId) to use (found in Portal->Account); defaults to whatever is in '.beamable/connection-configuration.json'
  --pid <pid>                            PID (Realm ID) to use (found in Portal -> Games -> Any Realm's details); defaults to whatever is in '.beamable/connection-configuration.json'
  -q, --quiet                            When true, skip input waiting and use default arguments (or error if no defaults are possible) [default: False]
  --host <host>                          This option defines the target Beamable environment. Needed for private cloud customers to target their exclusive Beamable environment. Ignorable by everyone else. Stored in '.beamable/connection-configuration.json'
  --access-token <access-token>          The access token to use for the requests. It overwrites the logged in user stored in connection-auth.json for THIS INVOCATION ONLY
  --refresh-token <refresh-token>        A Refresh Token to use for the requests. It overwrites the logged in user stored in connection-auth.json for THIS INVOCATION ONLY
  --log, --logs <log>                    Extra logs gets printed out
  --no-redirect                          If there is a local dotnet tool installation (with a ./config/dotnet-tools.json file) for the beam tool, then any global invocation of the beam tool will automatically redirect and call the local version. However, there will be a performance penalty due to the extra process invocation. This option flag will cause an error to occur instead of automatically redirecting the execution to a new process invocation.
  -prf, --prefer-remote-federation       By default, any local CLI invocation that should trigger a Federation of any type will prefer locally running Microservices. However, if you need the CLI to use the remotely running Microservices, use this option to ignore locally running services.
  --unmask-logs                          By default, logs will automatically mask tokens. However, when this option is enabled, tokens will be visible in their full text. This is a security risk.
  --no-log-file                          By default, logs are automatically written to a temp file so that they can be used in an error case. However, when this option is enabled, logs are not written. Also, if the BEAM_CLI_NO_FILE_LOG environment variable is set, no log file will be written.  [default: False]
  --docker-cli-path <docker-cli-path>    a custom location for docker. By default, the CLI will attempt to resolve docker through its usual install locations. You can also use the BEAM_DOCKER_EXE environment variable to specify. 
                                         Currently, a docker path has been automatically identified. [default: docker]
  --emit-log-streams                     Out all log messages as data payloads in addition to however they are logged
  --add-project-path <add-project-path>  additional file paths to be included when building a local project manifest.
  --dir <dir>                            [DEPRECATED] Path override for the .beamable folder
  --raw                                  Output raw JSON to standard out. This happens by default when the command is being piped
  --pretty                               Output syntax highlighted box text. This happens by default when the command is not piped
  --dotnet-path <dotnet-path>            a custom location for dotnet [default: dotnet]
  -?, -h, --help                         Show help and usage information



 */
UCLASS()
class UBeamCliServicesRunCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliServicesRunStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (TArray<UBeamCliServicesRunStreamData*>& StreamData, TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;

	inline static FString StreamTypeLocalProgress = FString(TEXT("local_progress"));
	UPROPERTY() TArray<UBeamCliServicesRunLocalProgressStreamData*> LocalProgressStream;
	UPROPERTY() TArray<int64> LocalProgressTimestamps;
	TFunction<void (TArray<UBeamCliServicesRunLocalProgressStreamData*>& StreamData, TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnLocalProgressStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual bool HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer) override;
	virtual void HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer) override;
	virtual FString GetCommand() override;
};
