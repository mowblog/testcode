/*Please note the class should only build with MBCS mode, 
  do not support Unicode mode
*/
#include "stdafx.h"
#include "LDK.h"
#include "vendor_Code.h"

/* Default constructor, initialize all variables */
LDK::LDK()
{
	handle = HASP_INVALID_HANDLE_VALUE;
	vendorCode = (char*)vendor_Code;
	feature = 0;
	status = 0;
	scope = scope_default;
	format = format4;
	hh = NULL;
	hc = NULL;
	ht = NULL;
	LDKTimer = 0.0;
	bt = { 0 };
	et = { 0 };
	QueryPerformanceFrequency(&fq);
}

INT LDK::Login(INT ft)
{
	QueryPerformanceCounter(&bt);
	status = hasp_login(ft, vendorCode, &handle);
	QueryPerformanceCounter(&et);
	LDKTimer = (double)(et.QuadPart - bt.QuadPart)*1000.0 / fq.QuadPart;
	if (status != 0)
	{
		return status;
	}
	else {
		if (hh == NULL || hc==NULL) {
			hh = (struct HASP_HANDLE *)malloc(sizeof(struct HASP_HANDLE));
				hh->handle = handle;
			hh->id = 1;
			hh->next = NULL;
			hh->prev = NULL;
			hc = hh;
		}
		else
		{
			hc->next = (struct HASP_HANDLE *)malloc(sizeof(struct HASP_HANDLE));
			hc->next->handle = handle;
			hc->next->id = hc->id + 1;
			hc->next->next = NULL;
			ht = hc;
			hc = hc->next;
			hc->prev = ht;
		}
	}
	return status;
}

INT LDK::LoginScope(INT f, CString  s)
{
	scope = s.GetBuffer(0);
	QueryPerformanceCounter(&bt);
	status = hasp_login_scope(f, scope, vendorCode, &handle);
	QueryPerformanceCounter(&et);
	LDKTimer = (double)(et.QuadPart - bt.QuadPart)*1000.0 / fq.QuadPart;
	if (status != 0)
	{
		return status;
	}
	else {
		if (hh == NULL || hc == NULL) {
			hh = (struct HASP_HANDLE *)malloc(sizeof(struct HASP_HANDLE));
			hh->handle = handle;
			hh->id = 1;
			hh->next = NULL;
			hh->prev = NULL;
			hc = hh;
		}
		else
		{
			hc->next = (struct HASP_HANDLE *)malloc(sizeof(struct HASP_HANDLE));
			hc->next->handle = handle;
			hc->next->id = hc->id + 1;
			hc->next->next = NULL;
			ht = hc;
			hc = hc->next;
			hc->prev = ht;
		}
	}
	return status;
}

CString  LDK::Encrypt(CString buf)
{
	if (hc == NULL)
	{
		status = -1;
		return NULL;
	}
	if (!CHECKHEXSTRING(buf))
	{
		status = -2;
		return NULL;
	}
	int cs_len = buf.GetLength();
	int len_t = cs_len/2;
	
	char *hexbuf = buf.GetBuffer(0);
	memset(Buf, '\0', BUFFER_LENGTH);
	hexToStr((unsigned char*)hexbuf, cs_len, (unsigned char*)Buf); /* Convert Hex String to char String */

	QueryPerformanceCounter(&bt);
	status = hasp_encrypt(hc->handle, Buf, len_t);
	QueryPerformanceCounter(&et);
	LDKTimer = (double)(et.QuadPart - bt.QuadPart)*1000.0 / fq.QuadPart; /* Convert the second to mili second */
	if (status != 0)
		return NULL;

	strToHex((unsigned char*)Buf, len_t, (unsigned char*)hexbuf); /* Convert char String to Hex String */

	CString tmp;
	tmp.Format("%s", hexbuf);
	return tmp;
}
CString LDK::Decrypt(CString buf)
{
	if (hc == NULL)
	{
		status = -1;
		return NULL;
	}
	if (!CHECKHEXSTRING(buf))
	{
		status = -2;
		return NULL;
	}

	int cs_len = buf.GetLength();
	int len_t = cs_len / 2;

	char* hexbuf = buf.GetBuffer(0);
	memset(Buf, '\0', BUFFER_LENGTH);
	hexToStr((unsigned char*)hexbuf, cs_len, (unsigned char*)Buf);

	QueryPerformanceCounter(&bt);
	status = hasp_decrypt(hc->handle, Buf, len_t);
	QueryPerformanceCounter(&et);
	LDKTimer = (double)(et.QuadPart - bt.QuadPart)*1000.0 / fq.QuadPart;
	if (status != 0)
		return NULL;

	strToHex((unsigned char*)Buf, len_t, (unsigned char*)hexbuf);
	CString tmp;
	tmp.Format("%s", hexbuf);
	return tmp;
}
CString LDK::GetInfo(CString s, CString f)
{
	scope = s.GetBuffer(0);
	format = f.GetBuffer(0);
	char *info;

	QueryPerformanceCounter(&bt);
	status = hasp_get_info(scope, format, vendorCode, &info);
	QueryPerformanceCounter(&et);
	LDKTimer = (double)(et.QuadPart - bt.QuadPart)*1000.0 / fq.QuadPart;
	if (status != 0)
		return NULL;
	
	CString Info;
	Info.Format("%s",info);
	Info.Replace("\n", "\r\n"); //替换原始串中的\n为\r\n,便于显示

	return Info;
}
int LDK::Logout()
{
	if (hc == NULL)
	{
		status = -1;
		return NULL;
	}
	else {
		QueryPerformanceCounter(&bt);
		status = hasp_logout(hc->handle);
		QueryPerformanceCounter(&et);
		LDKTimer = (double)(et.QuadPart - bt.QuadPart)*1000.0 / fq.QuadPart;
		if (status != 0)
		{
			return status;
		}
		else if (hc->prev==NULL) {
			free(hc);
			hc = NULL;
		}
		else
		{
			ht = hc;
			hc = hc->prev;
			free(ht);
			ht = NULL;
		}

	}
	return status;
}
CString LDK::Read(UINT fileid, UINT offset, UINT length)
{
	if (hc == NULL)
	{
		status = -1;
		return NULL;
	}

	memset(Buf, '\0', BUFFER_LENGTH);
	QueryPerformanceCounter(&bt);
	status = hasp_read(hc->handle, fileid, offset, length, Buf);
	QueryPerformanceCounter(&et);
	LDKTimer = (double)(et.QuadPart - bt.QuadPart)*1000.0 / fq.QuadPart;
	if (status != 0)
	{
		return NULL;
	}
	memset(HexBuf, '\0', BUFFER_LENGTH * 2);
	strToHex((unsigned char*)Buf, length, (unsigned char*)HexBuf);

	CString ReadString;
	ReadString.Format("%s", HexBuf);
	//delete buf;
	return ReadString;
}
CString LDK::Write(UINT fileid, UINT offset, CString buf)
{

	int len,cs_len;

	if (hc == NULL)
	{
		status = -1;
		return NULL;
	}
	if (!CHECKHEXSTRING(buf))
	{
		status = -2;
		return NULL;
	}
	
	cs_len = buf.GetLength();
	len = cs_len / 2;
	char *hex_wbuf = buf.GetBuffer(0);
	memset(Buf, '\0', BUFFER_LENGTH);
	hexToStr((unsigned char*)hex_wbuf, (unsigned int)cs_len, (unsigned char*)Buf);

	QueryPerformanceCounter(&bt);
	status = hasp_write(hc->handle, fileid, offset, len, Buf);
	QueryPerformanceCounter(&et);
	LDKTimer = (double)(et.QuadPart - bt.QuadPart)*1000.0 / fq.QuadPart;
	if (status != 0)
	{
		return NULL;
	}

	CString Temp(hex_wbuf);
	return Temp;
}

/* check the string is a hex string or not:
 * 1.the length of string must be a multiple of 2
 * 2.each character in the string must be in "0123456789ABCDEFabcdef" */
BOOL LDK::CHECKHEXSTRING(CString hexString)
{
	CString Hex = "0123456789ABCDEFabcdef";
	if (hexString.GetLength() % 2 != 0)
	{
		return FALSE;
	}
	for (int i = 0; i < hexString.GetLength(); i++)
	{
		if (Hex.Find(hexString.GetAt(i)) == -1)
			return FALSE;
	}
	return TRUE;
}

int LDK::strToHex(unsigned char *cstring, unsigned int c_len, unsigned char *hstring)
{
	unsigned char tmp = 0;
	unsigned int len = 0;
	unsigned char* hex = hstring;
	if (cstring == NULL || hex == NULL ) {
		return -1;
	}
	
	while (len<c_len) {
		tmp = *cstring++;
		*hex++ = valueToHexCh((tmp & 0xF0) >> 4); //先写高字节
		*hex++ = valueToHexCh(tmp & 0x0F); //其次写低字节
		len++;
	}
	return 0;
}

int LDK::hexToStr(unsigned char *hstring, unsigned int h_len, unsigned char *cstring)
{
	unsigned char high, low;
	unsigned char tmp = 0;
	if (hstring == NULL || cstring == NULL || strlen((char*)hstring)%2==1) {
		return -1;
	}
	unsigned int i = 0;
	while (i++<h_len) {
		high = hexCharToValue(*hstring++);
		low = hexCharToValue(*hstring++);
		tmp = (high << 4) + low;
		*cstring++ = (char)tmp;
	}
	return 0;
}

unsigned int LDK::hexCharToValue(const unsigned char ch)
{
	unsigned int result=0;
	//获取16进制的高字节位数据
	if (ch >= '0' && ch <= '9') {
		result = (unsigned int)(ch - '0');
	}
	else if (ch >= 'a' && ch <= 'z') {
		result = (unsigned int)(ch - 'a') + 10;
	}
	else if (ch >= 'A' && ch <= 'Z') {
		result = (unsigned int)(ch - 'A') + 10;
	}

	return result;
}

unsigned char LDK::valueToHexCh(const unsigned int value)
{
	unsigned char result = '\0';
	if (value >= 0 && value <= 9) {
		result = (unsigned char)(value + '0'); //48为ascii编码的‘0’字符编码值
	}
	else if (value >= 10 && value <= 15) {
		result = (unsigned char)(value - 10 + 'A'); //减去10则找出其在16进制的偏移量，65为ascii的'A'的字符编码值
	}
	return result;
}

