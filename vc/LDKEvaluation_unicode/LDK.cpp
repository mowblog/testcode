#include "stdafx.h"
#include "LDK.h"

LDK::LDK(){}

LDK::LDK(char* vc)
{
	handle = HASP_INVALID_HANDLE_VALUE;
	vendorCode = (char*)calloc(1, strlen(vc) + 1);
	memcpy(vendorCode,vc,strlen(vc));
	feature = 0;
	USES_CONVERSION;
	scope = W2A(scope_default);
	format = W2A(format4);
	hh = NULL;
	hc = NULL;
	ht = NULL;
	QueryPerformanceFrequency(&fq);
}

INT LDK::Login(INT ft)
{
	QueryPerformanceCounter(&bt);
	status = hasp_login(ft, vendorCode, &handle);
	QueryPerformanceCounter(&et);
	LDKTimer = (double)(et.QuadPart - bt.QuadPart)*1.0 / fq.QuadPart;
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

int LDK::LoginScope(int f, CString s)
{
	int n = s.GetLength();
	int len = WideCharToMultiByte(CP_ACP, 0, s, n, NULL, 0, NULL, NULL);
	char* sc = (char*)calloc(len + 1,sizeof(char));
	WideCharToMultiByte(CP_ACP, 0, s, n, sc, len, NULL, NULL);
	QueryPerformanceCounter(&bt);
	status = hasp_login_scope(f, sc, vendorCode, &handle);
	QueryPerformanceCounter(&et);
	LDKTimer = (double)(et.QuadPart - bt.QuadPart)*1.0 / fq.QuadPart;
	if (status != 0)
	{
		return status;
	}
	else {
		if (hh == NULL) {
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

CString LDK::Encrypt(CString buf, UINT length)
{
	if (hc == NULL)
	{
		status = -1;
		return NULL;
	}
	INT n = buf.GetLength();
	INT len = WideCharToMultiByte(CP_ACP, 0, buf, n, NULL, 0, NULL, NULL);
	if (len % 2 != 0)
	{
		status = -2;
		return NULL;
	}
	char* enbuf_hex = (char*)calloc(len + 1, 1);
	WideCharToMultiByte(CP_ACP, 0, buf, n, enbuf_hex, len, NULL, NULL);
	char* enbuf = (char*)calloc(length + 1, 1);
	hexToStr(enbuf_hex,len, enbuf);
	memset(enbuf_hex, '\0', len + 1);
	QueryPerformanceCounter(&bt);
	status = hasp_encrypt(hc->handle, enbuf, length);
	QueryPerformanceCounter(&et);
	LDKTimer = (double)(et.QuadPart - bt.QuadPart)*1.0 / fq.QuadPart;
	enbuf[len/2 + 1] = '\0';
	strToHex((unsigned char*)enbuf, length, enbuf_hex);
	CString tmp;
	//char* aa = "125D67BFFCAEB0661A08FAA5137A57CA";
	//tmp.Format(L"%s", aa);
	USES_CONVERSION;
	tmp=A2W(enbuf_hex);
	return tmp;
}
CString LDK::Decrypt(CString buf, UINT length)
{
	if (hc == NULL)
	{
		status = -1;
		return NULL;
	}
	int cs_len = buf.GetLength();
	//if the length of string is less than 16, return -3
	if (cs_len < 16)
	{
		return NULL;
		status = -3;
	}
	//get the MultiByte string's len
	int c_len = WideCharToMultiByte(CP_ACP, 0, buf, cs_len, NULL, 0, NULL, NULL);
	//if c_len
	if (c_len % 2 != 0)
	{
		status = -2;
		return NULL;
	}
	char* debuf_hex = (char*)calloc(c_len + 1, 1);
	WideCharToMultiByte(CP_ACP, 0, buf, cs_len, debuf_hex, c_len, NULL, NULL);

	if (length == 0)
		length = c_len;
	char* debuf = (char*)calloc(c_len /2 + 1, 1);
	hexToStr(debuf_hex, c_len, debuf);
	QueryPerformanceCounter(&bt);
	status = hasp_decrypt(hc->handle, debuf, length);
	QueryPerformanceCounter(&et);
	LDKTimer = (double)(et.QuadPart - bt.QuadPart)*1.0 / fq.QuadPart;
	debuf[length + 1] = '\0';
	strToHex((unsigned char*)debuf, length, debuf_hex);
	CString tmp;
	//tmp.Format(L"%s", debuf_hex);
	USES_CONVERSION;
	tmp = A2W(debuf_hex);
	return tmp;
}
CString LDK::GetInfo(CString s, CString f)
{
	USES_CONVERSION;
	scope = T2A(s);
	format = T2A(f);
	char *i;
	QueryPerformanceCounter(&bt);
	status = hasp_get_info(scope, format, vendorCode, &i); 
	QueryPerformanceCounter(&et);
	LDKTimer = (double)(et.QuadPart - bt.QuadPart)*1.0 / fq.QuadPart;
	if (status != 0)
		return NULL;
	int charLen = strlen(i);
	int len = MultiByteToWideChar(CP_ACP, 0, i, charLen, NULL, 0);
	WCHAR *buf = new WCHAR[len + 1];
	MultiByteToWideChar(CP_ACP, 0, i, charLen, buf, len);
	buf[len] = '\0';
	CString info;
	info.Append(buf);
	info.Replace(L"\n", L"\r\n"); //替换原始串中的\n为\r\n,便于显示
	return info;
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
		LDKTimer = (double)(et.QuadPart - bt.QuadPart)*1.0 / fq.QuadPart;
		if (status != 0)
		{
			return status;
		}
		else {
			ht = hc;
			hc = hc->prev;
			free(ht);
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
	//readbuf from HASP API directy
	char* rbuf = (char*)calloc(length+1, 1);
	QueryPerformanceCounter(&bt);
	status = hasp_read(hc->handle, fileid, offset, length, rbuf);
	QueryPerformanceCounter(&et);
	LDKTimer = (double)(et.QuadPart - bt.QuadPart)*1.0 / fq.QuadPart;
	//convert readbuf to hex string
	char* rbuf_hex = (char*)calloc(length*2 + 1, 1);
	strToHex((unsigned char*)rbuf, length, rbuf_hex);
	int n = MultiByteToWideChar(CP_ACP, 0, rbuf_hex, length*2, NULL, 0);
	wchar_t* buf = new wchar_t[n+1];
	memset(buf, '\0', n + 1);
	MultiByteToWideChar(CP_ACP, 0, rbuf_hex, length * 2, buf, n);
	buf[n] = '\0';
	CString r;
	r.Append(buf);
	//delete buf;
	return r;
}
int LDK::Write(UINT fileid, UINT offset, UINT length, CString buf)
{
	if (hc == NULL)
	{
		status = -1;
		return NULL;
	}
	int n = buf.GetLength();
	int h_len = WideCharToMultiByte(CP_ACP, 0, buf, n, NULL, 0, NULL, NULL);
	char* wbuf_hex = (char*)calloc(h_len +1,1);
	WideCharToMultiByte(CP_ACP, 0, buf, n, wbuf_hex, h_len, NULL, NULL);
	wbuf_hex[h_len + 1] = '\0';
	//convert to char string
	char* wbuf = (char*)calloc(h_len / 2 + 1, 1);
	hexToStr(wbuf_hex, h_len, wbuf);
	QueryPerformanceCounter(&bt);
	status = hasp_write(hc->handle, fileid, offset, length, wbuf);
	QueryPerformanceCounter(&et);
	LDKTimer = (double)(et.QuadPart - bt.QuadPart)*1.0 / fq.QuadPart;
	return status;
}

int LDK::strToHex(unsigned char *cstring, unsigned int c_len, char *hstring)
{
	unsigned short tmp = 0;
	unsigned int len = 0;
	char* hex = hstring;
	if (cstring == NULL || hex == NULL || c_len <= 0) {
		return -1;
	}
	
	while (len++<c_len) {
		tmp = (unsigned int)*cstring++;
		*hex++ = valueToHexCh((tmp & 0xF0) >> 4); //先写高字节
		*hex++ = valueToHexCh(tmp & 0x0F); //其次写低字节
	}
	return 0;
};
int LDK::hexToStr(char *hstring, unsigned int h_len, char *cstring)
{
	int high, low;
	int tmp = 0;
	if (hstring == NULL || cstring == NULL || strlen(hstring)%2==1) {
		return -1;
	}
	int i = 0;
	while (i<h_len) {
		high = hexCharToValue(*hstring++);
		low = hexCharToValue(*hstring++);
		tmp = (high << 4) + low;
		*cstring++ = (char)tmp;
		i++;
	}
	return 0;
};
int LDK::hexCharToValue(const char ch)
{
	int result = 0;
	//获取16进制的高字节位数据
	if (ch >= '0' && ch <= '9') {
		result = (int)(ch - '0');
	}
	else if (ch >= 'a' && ch <= 'z') {
		result = (int)(ch - 'a') + 10;
	}
	else if (ch >= 'A' && ch <= 'Z') {
		result = (int)(ch - 'A') + 10;
	}

	return result;
};
char LDK::valueToHexCh(const unsigned int value)
{
	char result = '\0';
	if (value >= 0 && value <= 9) {
		result = (char)(value + '0'); //48为ascii编码的‘0’字符编码值
	}
	else if (value >= 10 && value <= 15) {
		result = (char)(value - 10 + 'A'); //减去10则找出其在16进制的偏移量，65为ascii的'A'的字符编码值
	}
	return result;
};