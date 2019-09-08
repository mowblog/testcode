using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using MyDll;

namespace HelloWorld
{
    public partial class _Default : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            DllSample cl = new DllSample("Csharp Web dll 外壳加密测试");
            Label1.Text = cl.GetHello();
        }
    }
}
