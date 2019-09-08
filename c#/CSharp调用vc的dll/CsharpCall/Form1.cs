using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ManageCppDll;

namespace CsharpCall
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            HaspTestManage htm = new HaspTestManage();
            int status = htm.HaspCheck2(0);
            textBox1.Text = "login:" + status;
        }

    }
}
