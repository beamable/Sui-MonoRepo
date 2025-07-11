using System;
using System.Threading.Tasks;
using Beamable.Server;
using Beamable.SuiFederation.Features.Enoki.Models;
using Beamable.SuiFederation.Features.OAuthProvider.Exceptions;
using Beamable.SuiFederation.Features.OAuthProvider.Storage.Models;
using MongoDB.Bson;
using MongoDB.Driver;

namespace Beamable.SuiFederation.Features.OAuthProvider.Storage;

public class OAuthRequestCollection(IStorageObjectConnectionProvider storageObjectConnectionProvider, Configuration configuration)
    : IService
{
    private IMongoCollection<OAuthRequestData>? _collection;

    private async ValueTask<IMongoCollection<OAuthRequestData>> Get()
    {
        if (_collection is not null) return _collection;
        _collection =
            (await storageObjectConnectionProvider.SuiFederationStorageDatabase()).GetCollection<OAuthRequestData>("oauth-requests");
        await _collection.Indexes.CreateManyAsync([
            new CreateIndexModel<OAuthRequestData>(Builders<OAuthRequestData>.IndexKeys
                .Ascending(x => x.GamerTag)
                .Ascending(x => x.Network)),
            new CreateIndexModel<OAuthRequestData>(Builders<OAuthRequestData>.IndexKeys
                .Ascending(x => x.Nonce)
                .Ascending(x => x.Network)),
            new CreateIndexModel<OAuthRequestData>(Builders<OAuthRequestData>.IndexKeys
                .Ascending(x => x.GamerTag)
                .Ascending(x => x.ClientId)
                .Ascending(x => x.Network))
        ]);
        return _collection;
    }

    public async Task Insert(OAuthRequestData model)
    {
        try
        {
            var collection = await Get();
            var filter = Builders<OAuthRequestData>.Filter.And(
                Builders<OAuthRequestData>.Filter.Eq(m => m.GamerTag, model.GamerTag),
                Builders<OAuthRequestData>.Filter.Eq(m => m.ClientId, model.ClientId)
            );

            var update = Builders<OAuthRequestData>.Update
                .SetOnInsert(x => x.Id, ObjectId.GenerateNewId())
                .Set(x => x.GamerTag, model.GamerTag)
                .Set(x => x.ClientId, model.ClientId)
                .Set(x => x.Network, model.Network)
                .Set(x => x.Nonce, model.Nonce)
                .Set(x => x.Randomness, model.Randomness)
                .Set(x => x.Epoch, model.Epoch)
                .Set(x => x.MaxEpoch, model.MaxEpoch)
                .Set(x => x.Url, model.Url)
                .Set(x => x.Token, "")
                .Set(x => x.Address, new AddressData())
                .Set(x => x.TimeStamp, DateTime.UtcNow);

            await collection.UpdateOneAsync(filter, update, new UpdateOptions { IsUpsert = true });
        }
        catch (Exception e)
        {
            throw new OauthProviderException($"Error inserting OAuth request: {e.Message}");
        }
    }

    public async Task UpdateToken(ObjectId id, string jwt)
    {
        var collection = await Get();
        var filter = Builders<OAuthRequestData>.Filter.Eq(m => m.Id, id);
        var update = Builders<OAuthRequestData>.Update
            .Set(x => x.Token, jwt);
        await collection.UpdateOneAsync(filter, update);
    }

    public async Task UpdateAddress(ObjectId id, EnokiAddressData address)
    {
        var collection = await Get();
        var filter = Builders<OAuthRequestData>.Filter.Eq(m => m.Id, id);
        var update = Builders<OAuthRequestData>.Update
            .Set(x => x.Address, address.ToAddressData());
        await collection.UpdateOneAsync(filter, update);
    }

    public async Task<OAuthRequestData?> GetByNonce(string nonce)
    {
        var collection = await Get();
        var network = await configuration.SuiEnvironment;
        return await collection.Find(c => c.Nonce == nonce && c.Network == network).FirstOrDefaultAsync();
    }

    public async Task<OAuthRequestData?> GetById(string id)
    {
        var collection = await Get();
        return await collection.Find(c => c.Id == ObjectId.Parse(id)).FirstOrDefaultAsync();
    }

    public async Task<OAuthRequestData?> GetByGamer(long gamerTag, string clientId)
    {
        var collection = await Get();
        var network = await configuration.SuiEnvironment;
        return await collection.Find(c => c.GamerTag == gamerTag && c.ClientId == clientId && c.Network == network).FirstOrDefaultAsync();
    }
}