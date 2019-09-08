using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace mfc_NativeDll_Test
{
    class mfcNativeDll
    {
        [DllImport("mfc_NativeDll.dll", CharSet = CharSet.Ansi)]
        public static extern int m_add(int a, int b);


        public int mfcNative_Add(int a, int b)
        {
            return m_add(a, b);
        }
    }
}
