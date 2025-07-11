using System;
using System.IdentityModel.Tokens.Jwt;
using System.Text.Json;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Common.Api;
using Beamable.SuiFederation.Caching;
using Beamable.SuiFederation.Features.Enoki;
using Beamable.SuiFederation.Features.Enoki.Models;
using Beamable.SuiFederation.Features.HttpService;
using Beamable.SuiFederation.Features.OAuthProvider.Exceptions;
using Beamable.SuiFederation.Features.OAuthProvider.Models;
using Beamable.SuiFederation.Features.OAuthProvider.Storage;
using Beamable.SuiFederation.Features.OAuthProvider.Storage.Models;
using Microsoft.IdentityModel.Tokens;
using SuiFederationCommon;
using SuiFederationCommon.Models.Oauth;

namespace Beamable.SuiFederation.Features.OAuthProvider;

public class GoogleProvider : IService, IOauthProvider
{
    private readonly EnokiService _enokiService;
    private readonly OAuthRequestCollection _oAuthRequestCollection;
    private readonly Configuration _configuration;
    private readonly HttpClientService _httpClientService;
    private readonly IBeamableRequester _beamableRequester;

    private readonly MemoryCache<JwkSet> _jwkCache = new(TimeSpan.FromMinutes(30));

    public GoogleProvider(EnokiService enokiService, OAuthRequestCollection oAuthRequestCollection, Configuration configuration, HttpClientService httpClientService, IBeamableRequester beamableRequester)
    {
        _enokiService = enokiService;
        _oAuthRequestCollection = oAuthRequestCollection;
        _configuration = configuration;
        _httpClientService = httpClientService;
        _beamableRequester = beamableRequester;
    }

    public async Task<string> GetAuthorizationUrl(long gamerTag)
    {
        var metadata = await _enokiService.GetAppMetadata();
        var clientId = metadata.GetProviderClientId(OauthProvider.Google);
        var nonceData = await _enokiService.CreateNonce();
        var state = CreateOAuthStatePayloadExtensions.GenerateStateParameter(gamerTag ,OauthProvider.Google, nonceData.Data.Nonce);
        var redirectUri = $"https://api.beamable.com/basic/{_beamableRequester.Cid}.{_beamableRequester.Pid}.micro_{SuiFederationSettings.MicroserviceName}/OAuthCallback";
        var url = $"https://accounts.google.com/o/oauth2/v2/auth?client_id={clientId}&response_type=id_token&scope=openid&redirect_uri={redirectUri}&nonce={nonceData.Data.Nonce}&response_mode=form_post&state={state}";
        await _oAuthRequestCollection.Insert(new OAuthRequestData
        {
            GamerTag = gamerTag,
            ClientId = clientId,
            Network = await _configuration.SuiEnvironment,
            Nonce = nonceData.Data.Nonce,
            Randomness = nonceData.Data.Randomness,
            Epoch = nonceData.Data.Epoch,
            MaxEpoch = nonceData.Data.MaxEpoch,
            Url = url
        });
        return url;
    }

    public async Task<OAuthDto> Validate(OauthCallbackRequest callbackRequest)
    {
        try
        {
            var state = CreateOAuthStatePayloadExtensions.ParseState(callbackRequest.State);
            var oAuthRequest = await _oAuthRequestCollection.GetByNonce(state.Nonce);
            if (oAuthRequest is null)
            {
                BeamableLogger.LogWarning("OAuth request not found for the provided nonce {0} and user {1}", state.Nonce, state.GamerTag);
                return OAuthRequestDataExtensions.Failed();
            }

            var metadata = await _enokiService.GetAppMetadata();
            var clientId = metadata.GetProviderClientId(OauthProvider.Google);

            var jwkSet = await GetJwkSet();
            var keys = new JsonWebKeySet(JsonSerializer.Serialize(jwkSet)).Keys;
            var validationParams = new TokenValidationParameters
            {
                ValidIssuer = "https://accounts.google.com",
                ValidAudience = clientId,
                ValidateIssuer = true,
                ValidateAudience = true,
                ValidateLifetime = true,
                ValidateIssuerSigningKey = true,
                IssuerSigningKeys = keys,
                ClockSkew = TimeSpan.FromMinutes(5)
            };

            var handler = new JwtSecurityTokenHandler();
            handler.InboundClaimTypeMap.Clear();
            var claimsPrincipal = handler.ValidateToken(callbackRequest.Token, validationParams, out _);
            if (!claimsPrincipal.IsValid(state))
            {
                BeamableLogger.LogWarning("Invalid token received for gamer {GamerTag}. Claims principal is not valid.", oAuthRequest.GamerTag);
                return OAuthRequestDataExtensions.Failed();
            }
            await _oAuthRequestCollection.UpdateToken(oAuthRequest.Id, callbackRequest.Token);
            return oAuthRequest.ToDto();
        }
        catch (Exception e)
        {
            BeamableLogger.LogWarning("Failed to validate Google OAuth callback: {0}", e.Message);
            return OAuthRequestDataExtensions.Failed();
        }
    }

    public async Task<EnokiAddress?> ResolveAddress(long gamerTag, string challenge, string solution)
    {
        try
        {
            var requestData = await _oAuthRequestCollection.GetById(solution);
            if (requestData is null)
            {
                BeamableLogger.LogWarning("OAuth request not found for solution", solution);
                return null;
            }

            var challengeUri = new Uri(challenge);
            if (!challengeUri.ValidateChallengeUri(requestData) || gamerTag != requestData.GamerTag)
            {
                BeamableLogger.LogWarning("Failed to validate challenge for gamerTag: {gamerTag} with solution: {solution}", gamerTag, solution);
                return null;
            }

            var addressData = await _enokiService.GetAddress(requestData.Token);
            if (addressData is null)
            {
                BeamableLogger.LogWarning("Failed to resolve address for gamerTag: {gamerTag} with solution: {solution}", gamerTag, solution);
                return null;
            }
            await _oAuthRequestCollection.UpdateAddress(requestData.Id, addressData.Data);
            return addressData;
        }
        catch (Exception e)
        {
            BeamableLogger.LogWarning("Failed to resolve Google OAuth: {0}", e.Message);
            return null;
        }
    }

    private async Task<JwkSet> GetJwkSet()
    {
        return await _jwkCache.GetOrAddAsync("google-jwkCache", async () =>
        {
            var data = await _httpClientService.Get<JwkSet>("https://www.googleapis.com/oauth2/v3/certs");
            return data;
        }) ?? throw new OauthProviderException("Failed to retrieve certs from Google.");
    }
}