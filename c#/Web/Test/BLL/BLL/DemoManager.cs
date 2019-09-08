using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using DAL;

namespace BLL
{
    public class DemoManager
    {
        private DemoService demoService;

        public DemoManager()
        {
            demoService = new DemoService();
        }

        public string GetStr()
        {
            return demoService.GetStr();
        }













    }
}
