/*
* @file   faceall_sdk.h
* @Author Faceall Group Limited
* @brief  FaceSDK header for Faceall C API.
*
* Copyright (c) 2014-2015, Faceall Group Limited. All Rights Reserved.
*/
#ifndef LICENSE_H
#define LICENSE_H
#include "face/faceall_common.h"

//#include <WinSock2.h>  
//#include <Iphlpapi.h>
//#pragma comment(lib,"Iphlpapi.lib")

FACEALL_SDK_INTERFACE char* get_license();

FACEALL_SDK_INTERFACE bool verify_dog();

//FACEALL_SDK_INTERFACE bool check_mac();

#endif
