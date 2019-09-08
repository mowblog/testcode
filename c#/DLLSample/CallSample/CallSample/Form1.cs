using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using SampleDLL;



namespace CallSample
{

    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
           // System.Console.WriteLine("Calling methods from MathLibrary.DLL:");

            //if (args.Length != 2)
            //{
            //    System.Console.WriteLine("Usage: TestCode <num1> <num2>");
            //    return;
            //}

            //long num1 = long.Parse(args[0]);
            //long num2 = long.Parse(args[1]);
            long num1 = 111;
            long num2 = 222;

            long sum = AddClass.Add(num1, num2);
            long product = MultiplyClass.Multiply(num1, num2);
            MessageBox.Show(sum.ToString());
            MessageBox.Show(product.ToString());

            //System.Console.WriteLine("{0} + {1} = {2}", num1, num2, sum);
            //System.Console.WriteLine("{0} * {1} = {2}", num1, num2, product);
        }

    }
}
