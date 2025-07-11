using System.Text.Json.Serialization;

namespace Beamable.SuiFederation.Features.Enoki.Models;

public class EnokiNonce
{
    [JsonPropertyName("data")]
    public EnokiNonceData Data { get; set; } = new ();

    public class EnokiNonceData
    {
        [JsonPropertyName("nonce")]
        public string Nonce { get; set; } = "";

        [JsonPropertyName("randomness")]
        public string Randomness { get; set; } = "";

        [JsonPropertyName("epoch")]
        public long Epoch { get; set; }

        [JsonPropertyName("maxEpoch")]
        public long MaxEpoch { get; set; }

        [JsonPropertyName("estimatedExpiration")]
        public long EstimatedExpiration { get; set; }
    }
}

public class EnokiNonceRequest
{
    [JsonPropertyName("network")]
    public string SuiNetwork { get; set; } = "";

    [JsonPropertyName("ephemeralPublicKey")]
    public string PublicKey { get; set; } = "";

    [JsonPropertyName("additionalEpochs")]
    public int AdditionalEpochs { get; set; }
}