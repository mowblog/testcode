using System;
using System.Collections.Generic;
using System.Text;

namespace UnixTime
{
    class Program
    {
        static void Main(string[] args)
        {
            //DateTime UnixTime = new DateTime(1970-1-1 );
            DateTime UnixTime = new System.DateTime(1970,01,01,0,0,0);

            long sec = 0;

            Console.WriteLine("Please input the seconds");
            sec = Convert.ToInt64(Console.ReadLine());
            DateTime NowTime = UnixTime.AddSeconds(sec);

            Console.WriteLine(NowTime);


            Console.ReadLine();
        }
    }
}
