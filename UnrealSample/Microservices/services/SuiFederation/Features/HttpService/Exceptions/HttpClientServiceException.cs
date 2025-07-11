using System.Net;
using Beamable.Server;

namespace Beamable.SuiFederation.Features.HttpService.Exceptions;

public class HttpClientServiceException(string message)
    : MicroserviceException((int)HttpStatusCode.BadRequest, "HttpClientServiceException", message);