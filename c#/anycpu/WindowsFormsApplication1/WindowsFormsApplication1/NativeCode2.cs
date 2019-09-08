using System;

public class NativeCode2 : IDisposable
{
    public string rt;
    private bool disposed = false;

    public NativeCode2()
    { 
    }

    ~NativeCode2()
    {
        Dispose(false);
    }


    public void Dispose()
    {
        Dispose(true);
    }
    public void Dispose(bool disposing)
    {
        if (!this.disposed)
        {
            if (disposing)
            {
                //this.licHandle = 0;
                /* only MANAGED resource should be dispose     */
                /* here that implement the IDisposable		   */
                /* Interface 								   */
            }
            /* only UNMANAGED resource should be dispose here */
            /*												  */
        }
        disposed = true;
    }

    public string Test32()
    {
        string mesg;
        try
        {
            mesg = NativeCode.test32(32).ToString();
        }
        catch(SystemException e)
        {
            return e.ToString();
        }
        return mesg;
    }

    public string Test64()
    {
        string mesg;
        try
        {
            mesg = NativeCode.test64(64).ToString();
        }
        catch (SystemException e)
        {
            return e.ToString();
        }
        return mesg;
    }
}

