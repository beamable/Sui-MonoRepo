using System;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace SuiFederationCommon.Models.Notifications
{
    /// <summary>
    ///  Converts between JSON and IPlayerNotification types.
    /// </summary>
    public class NotificationConverter : JsonConverter<IPlayerNotification>
    {
        /// <summary>
        /// Reads JSON and converts it to an IPlayerNotification object.
        /// </summary>
        /// <param name="reader"></param>
        /// <param name="objectType"></param>
        /// <param name="existingValue"></param>
        /// <param name="hasExistingValue"></param>
        /// <param name="serializer"></param>
        /// <returns></returns>
        /// <exception cref="NotSupportedException"></exception>
        public override IPlayerNotification ReadJson(JsonReader reader, Type objectType, IPlayerNotification existingValue,
            bool hasExistingValue, JsonSerializer serializer)
        {
            var jsonObject = JObject.Load(reader);
            var context = jsonObject["Context"]?.ToString();

            return context switch
            {
                nameof(PlayerNotificationContext.InventoryTransaction) =>
                    jsonObject.ToObject<InventoryTransactionNotification>(serializer),

                nameof(PlayerNotificationContext.OauthContext) =>
                    jsonObject.ToObject<OAuthNotification>(serializer),

                _ => throw new NotSupportedException($"Context '{context}' is not supported.")
            };
        }

        /// <summary>
        /// Writes an IPlayerNotification object as JSON.
        /// </summary>
        /// <param name="writer"></param>
        /// <param name="value"></param>
        /// <param name="serializer"></param>
        public override void WriteJson(JsonWriter writer, IPlayerNotification value, JsonSerializer serializer)
        {
            var jo = JObject.FromObject(value, serializer);
            jo.WriteTo(writer);
        }

        /// <summary>
        /// Checks if the converter can write JSON.
        /// </summary>
        public override bool CanWrite => true;
        /// <summary>
        /// Checks if the converter can read JSON.
        /// </summary>
        public override bool CanRead => true;
    }
}