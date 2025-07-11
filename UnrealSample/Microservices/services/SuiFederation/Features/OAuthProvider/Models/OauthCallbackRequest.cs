using System.Text.Json.Serialization;

namespace Beamable.SuiFederation.Features.OAuthProvider.Models;

public class OauthCallbackRequest
{
    [JsonPropertyName("state")]
    public required string State { get; set; }

    [JsonPropertyName("id_token")]
    public required string Token { get; set; }
}