using System;
using Beamable.SuiFederation.Features.OAuthProvider.Models;
using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;

namespace Beamable.SuiFederation.Features.OAuthProvider.Storage.Models;

public class OAuthRequestData
{
    [BsonId]
    public ObjectId Id { get; set; }
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
    public DateTime TimeStamp { get; set; } = DateTime.UtcNow;
}

public class AddressData
{
    public string Address { get; set; } = "";
    public string Salt { get; set; } = "";
    public string PublicKey { get; set; } = "";
}

public static class OAuthRequestDataExtensions
{
    public static OAuthDto ToDto(this OAuthRequestData data)
    {
        return new OAuthDto
        {
            Id = data.Id.ToString(),
            GamerTag = data.GamerTag,
            ClientId = data.ClientId,
            Network = data.Network,
            Nonce = data.Nonce,
            Randomness = data.Randomness,
            Url = data.Url,
            Epoch = data.Epoch,
            MaxEpoch = data.MaxEpoch,
            Token = data.Token,
            Address = data.Address,
            State = OAuthResult.Authorized
        };
    }

    public static OAuthDto Failed()
    {
        return new OAuthDto
        {
            Id = "",
            GamerTag = 0,
            ClientId = "",
            Network = "",
            Nonce = "",
            Randomness = "",
            Url = "",
            Epoch = 0,
            MaxEpoch = 0,
            Token = "",
            Address = new AddressData(),
            State = OAuthResult.Denied
        };
    }
}