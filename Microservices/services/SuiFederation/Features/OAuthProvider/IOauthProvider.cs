using System.Threading.Tasks;
using Beamable.SuiFederation.Features.Enoki.Models;
using Beamable.SuiFederation.Features.OAuthProvider.Models;
using Beamable.SuiFederation.Features.OAuthProvider.Storage.Models;

namespace Beamable.SuiFederation.Features.OAuthProvider;

public interface IOauthProvider
{
    Task<string> GetAuthorizationUrl(long gamerTag);
    Task<OAuthDto> Validate(OauthCallbackRequest callbackRequest);
    Task<EnokiAddress?> Resolve(long gamerTag, string challenge, string solution);
}