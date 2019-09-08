using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using ManageCppDll;

namespace WebManageDll
{
    public partial class _Default : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            HaspTestManage htm = new HaspTestManage();
            int status = htm.HaspCheck2(0);
            TextBox1.Text = "login:" + status;

        }
    //    protected void Button1_Click(object sender, EventArgs e)
    //    {
    //        TextBox1.Text = "test";
    //    }
    }
}