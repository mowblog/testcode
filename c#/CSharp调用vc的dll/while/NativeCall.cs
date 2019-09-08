using System;
using ManageCppDll;

namespace NativeCall
{
	class Test
	{
		static void Main(String[] args)
		{
			int status;
			int num = 0;
			while(true)
			{
				HaspTestManage htm = new HaspTestManage();
				status = htm.HaspCheck2(0);
				Console.WriteLine(num +" - "+status);
				num++;
			}
		}
	}
}