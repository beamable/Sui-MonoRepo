using System.Collections.Generic;
using System.Linq;
using System.Text.Json.Serialization;

namespace Beamable.SuiFederation.Features.Enoki.Models;

public class EnokiAppMetadata
{
    [JsonPropertyName("data")]
    public AppMetadata Data { get; set; } = new ();

    public class AppMetadata
    {
        [JsonPropertyName("authenticationProviders")]
        public List<AuthenticationProvider> AuthenticationProviders { get; set; } = [];
    }

    public class AuthenticationProvider
    {
        [JsonPropertyName("providerType")]
        public string Provider { get; set; } = "";

        [JsonPropertyName("clientId")]
        public string ClientId { get; set; } = "";
    }

    public string GetProviderClientId(string provider)
    {
        foreach (var authProvider in Data.AuthenticationProviders.Where(authProvider => authProvider.Provider == provider))
        {
            return authProvider.ClientId;
        }
        return string.Empty;
    }
}