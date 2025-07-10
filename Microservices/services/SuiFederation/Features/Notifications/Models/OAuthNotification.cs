using System.Runtime.Serialization;
using SuiFederationCommon.Models.Oauth;

namespace Beamable.SuiFederation.Features.Notifications.Models;

public class OAuthNotification : IPlayerNotification
{
    public string Context => PlayerNotificationContext.OauthContext;
    public required string Id { get; init; }
    public required OAuthState State { get; init; }
}

public enum OAuthState
{
    [EnumMember(Value = "pending")]
    Pending,

    [EnumMember(Value = "authorized")]
    Authorized,

    [EnumMember(Value = "denied")]
    Denied,

    [EnumMember(Value = "expired")]
    Expired,

    [EnumMember(Value = "revoked")]
    Revoked
}