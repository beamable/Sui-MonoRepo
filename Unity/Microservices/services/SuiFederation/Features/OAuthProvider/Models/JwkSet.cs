using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace Beamable.SuiFederation.Features.OAuthProvider.Models;

public class JwkSet
{
    [JsonPropertyName("keys")]
    public List<JwkKey> Keys { get; set; } = [];
}

public class JwkKey
{
    [JsonPropertyName("alg")]
    public string Algorithm { get; set; } = string.Empty;

    [JsonPropertyName("e")]
    public string Exponent { get; set; } = string.Empty;

    [JsonPropertyName("kty")]
    public string KeyType { get; set; } = string.Empty;

    [JsonPropertyName("n")]
    public string Modulus { get; set; } = string.Empty;

    [JsonPropertyName("use")]
    public string Use { get; set; } = string.Empty;

    [JsonPropertyName("kid")]
    public string KeyId { get; set; } = string.Empty;
}