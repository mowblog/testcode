using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Management;


namespace WindowsFormsApplication1
{
    
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void GetPlatformInfo_Click(object sender, EventArgs e)
        {
            NativeCode2 nv2 = new NativeCode2();
            string sys86or64 = Distinguish64or32System();
            //MessageBox.Show("the platform is " + sys86or64);
            
            listBox1.Items.Add("AddressWidth:" + sys86or64);
            //test the native code
            if (sys86or64.CompareTo("32") == 0)
            {
                //string nv = NativeCode.test32(32).ToString();
                listBox1.Items.Add("Native return: " + nv2.Test32());
            }
            else
            {
                string nv = NativeCode.test64(64).ToString();
                listBox1.Items.Add("Native return: " + nv2.Test64());
            }

        }


        public static string Distinguish64or32System()
        {
        try
        {
        string addressWidth = String.Empty;
        ConnectionOptions mConnOption = new ConnectionOptions();
        ManagementScope mMs = new ManagementScope("\\\\localhost", mConnOption);
        ObjectQuery mQuery = new ObjectQuery("select AddressWidth from Win32_Processor");
        ManagementObjectSearcher mSearcher = new ManagementObjectSearcher(mMs, mQuery);
        ManagementObjectCollection mObjectCollection = mSearcher.Get();
        foreach (ManagementObject mObject in mObjectCollection)
        {
        addressWidth = mObject["AddressWidth"].ToString();
        }
        return addressWidth;
        }
        catch (Exception ex)
        {
        MessageBox.Show(ex.ToString());
        return String.Empty;
        }
        }

        private void Clear_Click(object sender, EventArgs e)
        {
            //textBox1.Text = "";
            listBox1.Items.Clear();
        }

        private void GetOSInfo_Click(object sender, EventArgs e)
        {
            int Major = System.Environment.OSVersion.Version.Major;
            int Minor = System.Environment.OSVersion.Version.Minor;
            //textBox1.Text =  "Major: " + Major.ToString() + "  Minor: " + Minor.ToString();
            listBox1.Items.Add("Major: " + Major.ToString() + "  Minor: " + Minor.ToString());

        }

        private void GetCurrInfo_Click(object sender, EventArgs e)
        {
            bool x  = Environment.Is64BitProcess;
            bool y = (IntPtr.Size == 8);
            
            if (x&y)
                //textBox1.Text = "Is64BitProcess: true";
                listBox1.Items.Add("Is64BitProcess: true");
            else
                //textBox1.Text = "Is64BitProcess: false";
                listBox1.Items.Add("Is64BitProcess: false");
        }


    }
    public sealed class ABC
    {
        [DllImport("kernel32.dll", SetLastError = true,CallingConvention = CallingConvention.Winapi)]
        public static extern bool IsWow64Process([In] IntPtr hProcess,[Out] out bool lpSystemInfo);

        public static bool Is64Bit()
        {
            bool retVal = false;
            IsWow64Process(System.Diagnostics.Process.GetCurrentProcess().Handle,out retVal);
            return retVal;
        }
    }

}
