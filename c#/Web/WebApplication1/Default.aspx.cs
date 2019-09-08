using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.HtmlControls;
using System.Web.SessionState;
using System.Threading;
using System.Text;
using System.IO;
using Aladdin.HASP;

namespace WebApplication1
{
     #region HASP 变量定义
    public class HaspWeb
    {
        public static Hasp hasp;
        public HaspFeature feature;
        public string vendorCode =
                "AzIceaqfA1hX5wS+M8cGnYh5ceevUnOZIzJBbXFD6dgf3tBkb9cvUF/Tkd/iKu2fsg9wAysYKw7RMAsV" +
                "vIp4KcXle/v1RaXrLVnNBJ2H2DmrbUMOZbQUFXe698qmJsqNpLXRA367xpZ54i8kC5DTXwDhfxWTOZrB" +
                "rh5sRKHcoVLumztIQjgWh37AzmSd1bLOfUGI0xjAL9zJWO3fRaeB0NS2KlmoKaVT5Y04zZEc06waU2r6" +
                "AU2Dc4uipJqJmObqKM+tfNKAS0rZr5IudRiC7pUwnmtaHRe5fgSI8M7yvypvm+13Wm4Gwd4VnYiZvSxf" +
                "8ImN3ZOG9wEzfyMIlH2+rKPUVHI+igsqla0Wd9m7ZUR9vFotj1uYV0OzG7hX0+huN2E/IdgLDjbiapj1" +
                "e2fKHrMmGFaIvI6xzzJIQJF9GiRZ7+0jNFLKSyzX/K3JAyFrIPObfwM+y+zAgE1sWcZ1YnuBhICyRHBh" +
                "aJDKIZL8MywrEfB2yF+R3k9wFG1oN48gSLyfrfEKuB/qgNp+BeTruWUk0AwRE9XVMUuRbjpxa4YA67SK" +
                "unFEgFGgUfHBeHJTivvUl0u4Dki1UKAT973P+nXy2O0u239If/kRpNUVhMg8kpk7s8i6Arp7l/705/bL" +
                "Cx4kN5hHHSXIqkiG9tHdeNV8VYo5+72hgaCx3/uVoVLmtvxbOIvo120uTJbuLVTvT8KtsOlb3DxwUrwL" +
                "zaEMoAQAFk6Q9bNipHxfkRQER4kR7IYTMzSoW5mxh3H9O8Ge5BqVeYMEW36q9wnOYfxOLNw6yQMf8f9s" +
                "JN4KhZty02xm707S7VEfJJ1KNq7b5pP/3RjE0IKtB2gE6vAPRvRLzEohu0m7q1aUp8wAvSiqjZy7FLaT" +
                "tLEApXYvLvz6PEJdj4TegCZugj7c8bIOEqLXmloZ6EgVnjQ7/ttys7VFITB3mazzFiyQuKf4J6+b/a/Y";

        public string HaspWebLogin()
        {
            string ret;
            feature = HaspFeature.FromFeature(8998);
            hasp = new Hasp(feature);

            string scope =
                "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" +
                "<haspscope>" +
                "    <hasp type=\"HASP-HL\" >" +
                "        <license_manager hostname=\"localhost\" />" +
                "    </hasp>" +
                "</haspscope>";

            HaspStatus status = hasp.Login(vendorCode, scope);

            if (HaspStatus.StatusOk != status)
                ret = status.ToString();
            else
            {
                ret = "login success\n";
            }
            return ret;
        }

        public string HaspWebRead()
        {
            string read, ret;
            HaspFile RO = hasp.GetFile(HaspFileId.ReadOnly);
            HaspFile RW = hasp.GetFile(HaspFileId.ReadWrite);
            byte[] ROData = new byte[100];
            byte[] RWData = new byte[100];

            HaspStatus status;
            status = RO.Read(ROData, 0, ROData.Length);
            if (HaspStatus.StatusOk != status)
            {
                ret = "RO read fail:" + status.ToString();
                return ret;
            }
            status = RW.Read(RWData, 0, RWData.Length);
            if (HaspStatus.StatusOk != status)
            {
                ret = "RW read fail:" + status.ToString();
                return ret;
            }

            read = "RO:\r\n" + System.Text.Encoding.Default.GetString(ROData) + "\r\nRW:\r\n" + System.Text.Encoding.Default.GetString(RWData);
            return read;
        }
        public string HaspWebLogout()
        {
            string ret;
            HaspStatus status = hasp.Logout();
            if (HaspStatus.StatusOk != status)
                ret = status.ToString();
            else
            {
                ret = "logout success\n";
            }
            return ret;
        }

     #endregion
    }
        public partial class _Default : System.Web.UI.Page
        {
            public HaspWeb haspweb = new HaspWeb();
            public static String retg;
            public void refresh()
            {
                while (true)
                {
                    login_TextBox.Text = retg;
                    ClientScriptManager cs = Page.ClientScript;
                    cs.RegisterClientScriptBlock(this.GetType(), "Refresh", "<script>window.setTimeout('location.href=default.aspx',2000);</script>");
                    Thread.Sleep(2000);
                }
            }

            protected void Page_Load(object sender, System.EventArgs e)
            {

            }

            #region Web 窗体设计器生成的代码
            override protected void OnInit(EventArgs e)
            {
                //
                // CODEGEN: 该调用是 ASP.NET Web 窗体设计器所必需的。
                //
                InitializeComponent();
                base.OnInit(e);
            }

            /// <summary>
            /// 设计器支持所需的方法 - 不要使用代码编辑器修改
            /// 此方法的内容。
            /// </summary>
            private void InitializeComponent()
            {

            }
            #endregion

            public class MyThread : _Default
            {
                public HaspWeb me;
                public int State = 0;//0-没有开始,1-正在运行,2-成功结束,3-失败结束
                public DateTime StartTime;
                public DateTime FinishTime;
                public DateTime ErrorTime;
                public string ret;
                //记录日志
                public string log;
                FileStream flog;
                StreamWriter sw;
                
                //flog = file1.ReadToEnd();

                private void threadFun()
                {
                    me = new HaspWeb();
                    string filename = "c:\\temp\\iis"+Thread.CurrentThread.ManagedThreadId.ToString()+".log";
                    flog = new FileStream(filename,FileMode.Append);
                    sw = new StreamWriter(flog);
                    

                    try
                    {
                        while (true)
                        {
                            retg = ""; //初始化清空消息
                            StartTime = DateTime.Now;
                            sw.Write(StartTime.ToString() + " - ");
                            sw.WriteLine(Thread.CurrentThread.ManagedThreadId.ToString());
                           //retg = "thread running..";
                            log = me.HaspWebLogin();
                            sw.WriteLine(log);
                            retg += log;
                            //login_TextBox.Text = ret;
                            log = me.HaspWebRead();
                            sw.WriteLine(log);
                            retg += log; 
                            //login_TextBox.Text = ret;
                            log = me.HaspWebLogout();
                            sw.WriteLine(log);
                            retg += log;
                            
                            Thread.Sleep(60000);
                            sw.Flush();
                            log = "";
                        }
                    }
                    catch
                    {
                        ErrorTime = DateTime.Now;
                        State = 3;
                        sw.Flush();
                    }
                    finally
                    {
                        FinishTime = DateTime.Now;
                        sw.Close();
                        flog.Close();
                    }

                }

                public void runMythread()
                {
                    lock (this)//确保临界区被一个Thread所占用
                    {
                        if (State != 1)
                        {
                            State = 1;
                            StartTime = DateTime.Now;
                            System.Threading.Thread thread = new System.Threading.Thread(new System.Threading.ThreadStart(threadFun));
                            thread.Start();
                        }
                    }
                }
            }


            protected void Button1_Click(object sender, System.EventArgs e)
            {
                #region 测试hasp login并发数
                login_TextBox.Text = "thread starting";
                MyThread test = new MyThread();
                test.runMythread();
                Thread.Sleep(3000);
                login_TextBox.Text = retg;

                //System.Threading.Thread thread = new System.Threading.Thread(new System.Threading.ThreadStart(refresh));
               // thread.Start();
                //Page.RegisterStartupScript("", "<script>window.setTimeout('location.href=location.href',1000);</script>");

                 /*
                string ret = hasp.HaspWebLogin();
                login_TextBox.Text = ret;
                ret = ret + hasp.HaspWebRead();
                login_TextBox.Text = ret;
                hasp.HaspWebLogout();
                Thread.Sleep(2000);
                 */

                #endregion

            }

            protected void Button2_Click(object sender, System.EventArgs e)
            {
                string ret = haspweb.HaspWebLogout();
                
                logout_TextBox.Text = ret;

            }


        }
   
}