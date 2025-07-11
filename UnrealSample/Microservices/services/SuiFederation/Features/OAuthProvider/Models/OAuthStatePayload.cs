using System;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;
using Beamable.SuiFederation.Features.OAuthProvider.Exceptions;

namespace Beamable.SuiFederation.Features.OAuthProvider.Models;

public class OAuthStatePayload
{
    [JsonPropertyName("provider")]
    public required string Provider { get; set; }
    [JsonPropertyName("nonce")]
    public required string Nonce { get; set; }
    [JsonPropertyName("gamerTag")]
    public required long GamerTag { get; set; }
}

public static class CreateOAuthStatePayloadExtensions
{
    public static string GenerateStateParameter(long gamerTag, string provider, string nonce)
    {
        var payload = new OAuthStatePayload
        {
            Provider = provider,
            Nonce = nonce,
            GamerTag = gamerTag
        };

        var json = JsonSerializer.Serialize(payload);
        var base64 = Convert.ToBase64String(Encoding.UTF8.GetBytes(json));
        return Uri.EscapeDataString(base64);
    }

    public static OAuthStatePayload ParseState(string base64State)
    {
        var json = Encoding.UTF8.GetString(Convert.FromBase64String(base64State));
        return JsonSerializer.Deserialize<OAuthStatePayload>(json) ?? throw new OauthProviderException("Unable to parse OAuth state payload.");
    }
}