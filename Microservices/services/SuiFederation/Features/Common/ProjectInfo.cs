namespace Beamable.SuiFederation.Features.Common;

public static class ProjectInfo
{
    public static string Cid { get; private set; } = "";
    public static string Pid { get; private set; } = "";

    public static void Initialize(string cid, string pid)
    {
        Cid = cid;
        Pid = pid;
    }
}