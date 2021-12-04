#ifndef __LDK_H__
#define __LDK_H__

#include "hasp_api.h"

#pragma comment(lib,"hasp_windows_demo.lib")
#pragma once

extern wchar_t* format0;
extern wchar_t* format1;
extern wchar_t* format2;
extern wchar_t* format3;
extern wchar_t* format4;

extern wchar_t* scope_default;
extern wchar_t* scope0;
extern wchar_t* scope1;
extern wchar_t* scope2;
extern wchar_t* scope3;
extern wchar_t* scope4;

class LDK 
{
public:
	//hasp define
	hasp_feature_t feature;
	//hasp_status_t status;
	int status;
	char* vendorCode;
	char* scope;
	char* format;
	hasp_handle_t handle;
	//time
	LARGE_INTEGER fq, bt, et;
	DOUBLE LDKTimer;

	struct HASP_HANDLE
	{
		hasp_handle_t handle;
		UINT id;
		struct HASP_HANDLE * prev;
		struct HASP_HANDLE * next;
	};

	struct HASP_HANDLE *hh;
	struct HASP_HANDLE *hc;
	struct HASP_HANDLE *ht;
	LDK();
	LDK(char* vendorCode);
	int Login(int ft);
	int LoginScope(int ft,CString scope);
	CString Encrypt(CString buf, UINT length);
	CString Decrypt(CString buf, UINT length);
	CString GetInfo(CString s, CString f);
	int Logout();
	CString Read(UINT fileid, UINT offset, UINT length);
	int Write(UINT fileid, UINT offset, UINT length, CString buf);

	int strToHex(unsigned char *cstring, unsigned int c_len, char *hstring);
	int hexToStr(char *hex, unsigned int h_len, char *ch);
	int hexCharToValue(const char ch);
	char valueToHexCh(const unsigned int value);
};
#endif /*__LDK_H__*/