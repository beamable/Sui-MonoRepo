using System.Text.Json.Serialization;
using Beamable.SuiFederation.Features.OAuthProvider.Storage.Models;

namespace Beamable.SuiFederation.Features.Enoki.Models;

public class EnokiAddress
{
    [JsonPropertyName("data")]
    public EnokiAddressData Data { get; set; } = new ();
}

public class EnokiAddressData
{
    [JsonPropertyName("salt")]
    public string Salt { get; set; } = "";

    [JsonPropertyName("address")]
    public string Address { get; set; } = "";

    [JsonPropertyName("publicKey")]
    public string PublicKey { get; set; } = "";
}

public static class EnokiAddressExtensions
{
    public static AddressData ToAddressData(this EnokiAddressData address)
    {
        return new AddressData
        {
            Address = address.Address,
            Salt = address.Salt,
            PublicKey = address.PublicKey
        };
    }
}