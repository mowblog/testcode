// ManageCppDll.h
#pragma once
//#define NATIVECPPDLL_CLSSS_EXPORTS

#include "..\\NativeCPPDll\NativeCPPDll\NativeCppDll.h"
using namespace System;

namespace ManageCppDll 
{
    public ref class HaspTestManage
    {
		// 包装所有类CPerson的公有成员函数
		public:
			HaspTestManage();
			~HaspTestManage();
			int HaspTestManage::HaspCheck2(int feature);
		private:
			// 类CPerson的指针，用来调用类CPerson的成员函数
			HaspTestNative *m_pImp;
    };
};