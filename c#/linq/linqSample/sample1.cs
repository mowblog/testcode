using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace linqSample
{
    class Program
    {
        static void Main(string[] args)
        {
            string [] languages = {"Java","C#","C++","Delphi","VB.net","VC.net","C++ Builder","Kylix","Perl","Python"};
            var query = from item in languages
                        orderby item
                        group item by item.Length into lengthGroups
                        orderby lengthGroups.Key descending
                        select lengthGroups;
      
　　        foreach (var item in query)
　　        {
　　        Console.WriteLine("strings of length {0}",item.Key);
　　        foreach (var val in item)
　　        {
　　        Console.WriteLine(val);
　　        }
　　        }
　　        Console.ReadLine(); 
        }
    }
}
