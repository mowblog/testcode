using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ReflectDLL
{
        public class ReflectTest
        {
            public ReflectTest() { }
            public string WriteString(string s)
            {
                return "欢迎您，" + s;
            }
            //静态函数
            public static string WriteName(string s)
            {
                return "欢迎您光临，" + s;
            }
            //不带参数的函数
            public string WriteNoPara()
            {
                return "您使用的是无参数方法";
            }
        }
}
