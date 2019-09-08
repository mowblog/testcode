using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.IO;
using System.Diagnostics;

namespace csharp2sql2005
{

    public partial class Form1 : Form
    {


        public Form1()
        {
            InitializeComponent();
        }

        Stopwatch sw = new Stopwatch();
        private void button1_Click(object sender, EventArgs e)
        {
            button1.Enabled = false;
            sw.Start();
            string result="";
            SqlConnection conn = new SqlConnection();
            conn.ConnectionString = "data source = 172.25.20.27,49201;initial catalog = AgentInfo; user id = agents;password = 88519191";
            conn.Open();
            if (conn.State == ConnectionState.Open)
                //Console.WriteLine("connection success");
                textBox1.Text = "connection success";
            else
                //Console.WriteLine("connection failed");
                textBox1.Text = "connection failed";

            string strCmd = "select distinct a.KeyContainerID,a.KeyIdentifier,a.CreationDate,b.KeyTypeID,b.ktos from KeyContainer a, HASPKey b order by a.KeyContainerID";
            string strCmd2 = "select KeyContainerID,KeyIdentifier,CreationDate from KeyContainer union all select KeyTypeID,ktos from HASPKey";
            SqlCommand cmd = new SqlCommand(strCmd, conn);

            SqlDataReader t_SqlDataReader = cmd.ExecuteReader();
            while (t_SqlDataReader.Read())
            {
                string aaa = "";
                //Console.WriteLine("{0}\t{1}\t{2}", t_SqlDataReader["id"], t_SqlDataReader["name"], t_SqlDataReader["address"]);
                aaa = string.Format("{0}\t{1}\t{2}\t{3}\t{4}", t_SqlDataReader["KeyContainerID"], t_SqlDataReader["KeyIdentifier"], t_SqlDataReader["CreationDate"],
                    t_SqlDataReader["KeyTypeID"],t_SqlDataReader["ktos"]);
                textBox1.SelectionStart = textBox1.Text.Length;
                textBox1.SelectedText = aaa + Environment.NewLine;
                textBox1.ScrollToCaret();
                //textBox1.Text += Environment.NewLine;
            }
            t_SqlDataReader.Close();
            conn.Close();
            sw.Stop();
            MessageBox.Show(sw.ElapsedMilliseconds.ToString());
            button1.Enabled = true;
        }
        

    }
}
