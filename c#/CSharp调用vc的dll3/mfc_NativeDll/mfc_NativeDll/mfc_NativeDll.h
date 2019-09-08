// mfc_NativeDll.h : main header file for the mfc_NativeDll DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Cmfc_NativeDllApp
// See mfc_NativeDll.cpp for the implementation of this class
//

class Cmfc_NativeDllApp : public CWinApp
{
public:
	Cmfc_NativeDllApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
