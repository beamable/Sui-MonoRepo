using System;

namespace Beamable.SuiFederation.Extensions;

public static class StringExtensions
{
    public static bool StartsWithFast(this string value, string prefix, StringComparison comparisonType = StringComparison.Ordinal)
    {
        if (string.IsNullOrWhiteSpace(value) || string.IsNullOrWhiteSpace(prefix))
            return false;
        return value.StartsWith(prefix, comparisonType);
    }
}