#ifndef __LDK_H__
#define __LDK_H__

#include "hasp_api.h"

extern char* format0;
extern char* format1;
extern char* format2;
extern char* format3;
extern char* format4;

extern char* scope_default;
extern char* scope0;
extern char* scope1;
extern char* scope2;
extern char* scope3;
extern char* scope4;

#define BUFFER_LENGTH 1024

class LDK 
{
public:
	hasp_feature_t feature;
	int status;
	char *vendorCode;
	char *scope;
	char *format;
	hasp_handle_t handle;

/* Define two array to store the char string,  to avoid malloc memory in LDK member functions
 * Buf - the original char string
 * HexBuf - converted string from char string, like 0123456789ABCDEF -> 30313233343536373839414243444546 */
	char Buf[BUFFER_LENGTH];
	char HexBuf[BUFFER_LENGTH * 2];
/* recorde each LDK API's excution time */
	LARGE_INTEGER fq, bt, et;
	DOUBLE LDKTimer; //ms

/* use two-way linked list to store the handles
 * hh - the head of the list
 * hc - current pointer of the list
 * ht - temporal pointer */
	struct HASP_HANDLE
	{
		hasp_handle_t handle;
		UINT id;
		struct HASP_HANDLE *prev;
		struct HASP_HANDLE *next;
	} *hh,*hc,*ht;

	LDK();
	INT Login(INT ft);
	INT LoginScope(INT ft,CString scope);
	CString  Encrypt(CString  buf);
	CString  Decrypt(CString  buf);
	CString  GetInfo(CString  s, CString  f);
	INT Logout();
	CString  Read(UINT fileid, UINT offset, UINT length);
	CString	Write(UINT fileid, UINT offset, CString buf);

	BOOL CHECKHEXSTRING(CString hexString);
	int strToHex(unsigned char *cstring, unsigned int c_len, unsigned char *hstring);
	int hexToStr(unsigned char *hex, unsigned int h_len, unsigned char *ch);
	unsigned int hexCharToValue(const unsigned char ch);
	unsigned char valueToHexCh(const unsigned int value);
};
#endif /*__LDK_H__*/