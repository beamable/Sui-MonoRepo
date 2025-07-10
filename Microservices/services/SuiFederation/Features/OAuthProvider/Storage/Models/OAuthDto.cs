namespace Beamable.SuiFederation.Features.OAuthProvider.Storage.Models;

public class OAuthDto
{
    public string Id { get; set; } = "";
    public long GamerTag { get; set; }
    public required string ClientId { get; set; }
    public required string Network { get; set; }
    public required string Nonce { get; set; }
    public required string Randomness { get; set; }
    public required string Url { get; set; }
    public long Epoch { get; set; }
    public long MaxEpoch { get; set; }
    public string Token { get; set; } = "";
    public AddressData Address { get; set; } =  new();
    public OAuthResult State { get; set; }

}

public enum OAuthResult
{
    Authorized,
    Denied
}