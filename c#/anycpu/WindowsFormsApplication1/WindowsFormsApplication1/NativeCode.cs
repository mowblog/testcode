using System.Runtime.InteropServices;

public sealed class NativeCode
{
    [DllImport("DLL.dll",
        CharSet = CharSet.Ansi,
        EntryPoint = "test64")]
    public static extern int test64(int x);

    [DllImport("DLL.dll",
    CharSet = CharSet.Ansi,
    EntryPoint = "test32")]
    public static extern int test32(int x);
}
