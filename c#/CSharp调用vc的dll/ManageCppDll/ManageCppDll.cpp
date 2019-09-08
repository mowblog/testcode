// ManageCppDll.cpp
#include "stdafx.h"
#include "ManageCppDll.h"
#include <vcclr.h>
namespace ManageCppDll 
{
    // 在构造函数中创建类CPerson的对象并在析构函数中将该对象销毁
    // 所有的成员函数实现都是通过指针m_pImp调用类CPerson的相应成员函数实现
    HaspTestManage::HaspTestManage()
    {
        m_pImp = new HaspTestNative();
    }

    HaspTestManage::~HaspTestManage()
    {
        // 在析构函数中删除CPerson对象
        delete m_pImp;
    }

	int HaspTestManage::HaspCheck2(int feature)
	{
		return m_pImp->HaspCheck(feature);
	}
  
};