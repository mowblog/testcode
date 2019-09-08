using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace reflection1
{
    class Program
    {
        public static void test1()
        {
            System.Reflection.Assembly ass;
            Type type;
            object obj;
            try
            {
                ass = System.Reflection.Assembly.LoadFile(@"F:\Learn\C#\reflect\ReflectDLL\ReflectDLL\bin\Release\ReflectDLL.dll");//要绝对路径
                type = ass.GetType("ReflectDLL.ReflectTest");//必须使用 名称空间+类名称
                System.Reflection.MethodInfo method = type.GetMethod("WriteString");//方法的名称
                obj = ass.CreateInstance("ReflectDLL.ReflectTest");//必须使用名称空间+类名称
                string s = (string)method.Invoke(obj, new string[] { "boygw" }); // 实例方法的调用            或：string s = (string)method.Invoke(obj,Object[] parametors = new Object[]{"param"});
                System.Console.WriteLine(s + "          ");
                method = type.GetMethod("WriteName");//方法的名称
                s = (string)method.Invoke(null, new string[] { "jianglijun" }); // 静态方法的调用
                System.Console.WriteLine(s + "            ");

                method = type.GetMethod("WriteNoPara");//无参数的实例方法
                s = (string)method.Invoke(obj, null);
                System.Console.WriteLine(s + "            ");
                method = null;
            }
            catch (Exception ex)
            {
                System.Console.WriteLine(ex + "            ");
            }
            finally
            {
                ass = null;
                type = null;
                obj = null;
            }
        }

        static void Main(string[] args)
        {
            // Using GetType to obtain type information:
            int i = 42;
            System.Type type = i.GetType();
            System.Console.WriteLine(type);

            // Using Reflection to get information from an Assembly:
            System.Reflection.Assembly o = System.Reflection.Assembly.Load("mscorlib.dll");
            System.Console.WriteLine(o.GetName());

            test1();

            System.Console.Read();
        }
    }
}
