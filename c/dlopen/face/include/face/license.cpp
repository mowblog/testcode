#include "face/license.h"
#include <face/faceall_sdk.h>
//#include "Dongle_API.h"
#include <stdio.h>



FACEALL_SDK_INTERFACE char *get_license(){
	return "Beijing Faceall Technology www.faceall.cn copyright 2016, license for micro pattern effective from 2016-02-01 - 2016-02-03\n";
}
/*
FACEALL_SDK_INTERFACE bool verify_dog(){
	// 读取狗的信息
	// add by huang
	DONGLE_HANDLE phDongle = NULL;
	DWORD ulkey = DONGLE_SUCCESS;

	int nCount = 0;
	char AdminPin[] = "945038F1D3BBCF8B";// 开发商PIN码
	int nRemainCount = 0;
	const char* hid[] = { "09", "1D", "16", "53", "03", "08", "01", "15" };// 加密狗ID
	ulkey = Dongle_Enum(NULL, &nCount);//枚举锁的数量
	if (ulkey != DONGLE_SUCCESS)
	{
		fprintf(stderr, "Enum Rockey ARM Failed!\n");
		return NULL;
	}

	DONGLE_INFO *pDongleInfo = NULL;
	pDongleInfo = (DONGLE_INFO *)malloc(nCount * sizeof(DONGLE_INFO));
	if (NULL == pDongleInfo)
	{
		fprintf(stderr, "malloc memory error!\n");
		return NULL;
	}

	ulkey = Dongle_Enum(pDongleInfo, &nCount);//获取加密锁的相关信息
	if (ulkey != DONGLE_SUCCESS)
	{
		fprintf(stderr, "Get Dongle ARM information Failed.\n");
		return NULL;
	}
	for (int k = 0; k < nCount; k++){
		for (int i = 0; i < 8; i++)
		{
			int value = 0;
			sscanf(hid[i], "%X", &value);
			if (value != pDongleInfo[k].m_HID[i]){
				ulkey = Dongle_Close(phDongle);//关闭加密锁
				if (NULL != pDongleInfo)
				{
					free(pDongleInfo);
					pDongleInfo = NULL;
				}
				fprintf(stderr, "Hardware ID not match!\n");
				return NULL;
			}
		}
	}
	ulkey = Dongle_Open(&phDongle, 0);
	ulkey = Dongle_VerifyPIN(phDongle, FLAG_ADMINPIN, AdminPin, &nRemainCount);

	BYTE dogkey[16] = { 0 };
	memset(dogkey, 0, 6);
	DWORD ulRet = Dongle_ReadFile(phDongle, 0x0003, 0, dogkey, 16);

	BYTE orikey[16] = { 119, 104, 111, 104, 117, 97, 110, 103, 112, 97, 112, 97, 119, 105, 116, 104 };
	for (int i = 0; i < 16; ++i){
		if (orikey[i] != dogkey[i]){
			fprintf(stderr, "aes-key in dog not match!\n");
			return NULL;
		}
	}
	ulkey = Dongle_Close(phDongle);//关闭加密锁
	if (NULL != pDongleInfo)
	{
		free(pDongleInfo);
		pDongleInfo = NULL;
	}

	return TRUE;

}
*/

//FACEALL_SDK_INTERFACE bool check_mac(){
//	return true;
//}


