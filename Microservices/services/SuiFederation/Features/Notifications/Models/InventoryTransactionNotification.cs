using SuiFederationCommon.Models.Oauth;

namespace Beamable.SuiFederation.Features.Notifications.Models;

public class InventoryTransactionNotification : IPlayerNotification
{
    public string Context => PlayerNotificationContext.InventoryTransaction;
    public required string Id { get; init; }
}