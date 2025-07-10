using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Beamable.SuiFederation.Caching;
using Beamable.SuiFederation.Features.Enoki.Exceptions;
using Beamable.SuiFederation.Features.Enoki.Models;
using Beamable.SuiFederation.Features.HttpService;
using Beamable.SuiFederation.Features.SuiApi;

namespace Beamable.SuiFederation.Features.Enoki;

public class EnokiService : IService
{
    private readonly HttpClientService _httpClientService;
    private readonly Configuration _configuration;
    private readonly MemoryCache<EnokiAppMetadata> _metadataCache = new(TimeSpan.FromMinutes(30));

    public EnokiService(HttpClientService httpClientService, Configuration configuration)
    {
        _httpClientService = httpClientService;
        _configuration = configuration;
    }

    public async Task<EnokiAppMetadata> GetAppMetadata()
    {
        return await _metadataCache.GetOrAddAsync("enokiMetadata", async () =>
        {
            var url = await _configuration.EnokiUrl + "/app";
            var data = await _httpClientService.Get<EnokiAppMetadata>(url,
                headers: new Dictionary<string, string>
                {
                    {
                        "Authorization", $"Bearer {await _configuration.EnokiApiKey}"
                    }
                });
            return data ?? throw new EnokiServiceException("Failed to retrieve app metadata from Enoki.");
        }) ?? throw new EnokiServiceException("Failed to retrieve app metadata from Enoki.");
    }

    public async Task<EnokiNonce> CreateNonce()
    {
        var ephemeralWallet = await SuiApiService.CreateEphemeral();
        var url = await _configuration.EnokiUrl + "/zklogin/nonce";
        var data = await _httpClientService.Post<EnokiNonce>(url,
            headers: new Dictionary<string, string>
            {
                {
                    "Authorization", $"Bearer {await _configuration.EnokiApiKey}"
                }
            },
            content: new EnokiNonceRequest
            {
                SuiNetwork = await _configuration.SuiEnvironment,
                PublicKey = ephemeralWallet.PublicKey,
                AdditionalEpochs = 0
            });
        return data ?? throw new EnokiServiceException("Failed to retrieve nonce from Enoki.");
    }

    public async Task<EnokiAddress?> GetAddress(string jwt)
    {
        var url = await _configuration.EnokiUrl + "/zklogin";
        return await _httpClientService.Get<EnokiAddress>(url,
            headers: new Dictionary<string, string>
            {
                {
                    "Authorization", $"Bearer {await _configuration.EnokiApiKey}"
                },
                {
                    "zklogin-jwt", jwt
                }
            });
    }
}