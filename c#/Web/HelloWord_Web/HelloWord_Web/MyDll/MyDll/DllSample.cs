using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MyDll
{
    public class DllSample
    {
        private String mystr;

        public DllSample()
        {
            mystr = "Hello World!";
        }

        public DllSample(string str)
        {
            mystr = str;
        }
        public string GetHello()
        {
            return mystr;
        }
    }
}
