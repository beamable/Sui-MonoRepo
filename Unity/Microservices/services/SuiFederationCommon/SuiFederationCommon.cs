﻿using Beamable.Common;

namespace SuiFederationCommon
{
    /// <summary>
    /// SuiWeb3Identity definition
    /// </summary>
    [FederationId(SuiFederationSettings.SuiIdentityName)]
    public class SuiWeb3Identity : IFederationId {}

    /// <summary>
    /// SuiWeb3ExternalIdentity definition
    /// </summary>
    [FederationId(SuiFederationSettings.SuiExternalIdentityName)]
    public class SuiWeb3ExternalIdentity : IFederationId {}

    /// <summary>
    /// SuiWeb3EnokiIdentity definition
    /// </summary>
    [FederationId(SuiFederationSettings.SuiEnokiIdentityName)]
    public class SuiWeb3EnokiIdentity : IFederationId {}

    /// <summary>
    /// WarpedFederationSettings class
    /// </summary>
    public static class SuiFederationSettings
    {
        ///<Summary>
        /// SuiFederation microservice name
        ///</Summary>
        public const string MicroserviceName = "SuiFederation";
        ///<Summary>
        /// SuiFederationIdentity name
        ///</Summary>
        public const string SuiIdentityName = "SuiIdentity";
        ///<Summary>
        /// SuiFederationIdentity name
        ///</Summary>
        public const string SuiExternalIdentityName = "SuiExternalIdentity";
        ///<Summary>
        /// SuiFederationIdentity name
        ///</Summary>
        public const string SuiEnokiIdentityName = "SuiEnokiIdentity";
    }

    /// <summary>
    /// Empty type used for SuiFederationCommon assembly load in the Federation service
    /// </summary>
    public class SuiFederationCommonAssemblyIdentifier {}
}