using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace mfc_NativeDll_Test
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
         int a,b,c,d;
            mfcNativeDll mnd = new mfcNativeDll();
            if(textBox1.Text==String.Empty)
                a = 0;
            else
                a =  Int32.Parse(textBox1.Text);

            if (textBox1.Text == String.Empty)
                b = 0;
            else
                b = Int32.Parse(textBox2.Text);

            Thread.Sleep(1000);
            mnd.mfcNative_Add(a, b);
            textBox3.Text = mnd.mfcNative_Add(a, b).ToString();
            Thread.Sleep(1000);
        }
    }

}
