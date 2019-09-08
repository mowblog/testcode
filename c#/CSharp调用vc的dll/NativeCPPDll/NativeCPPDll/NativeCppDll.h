// NativeCppDll.h
#pragma once

#ifndef NATIVECPPDLL_CLSSS_EXPORTS
    #define NATIVECPPDLL_CLSSS_EXPORTS __declspec(dllexport)
#else
    #define NATIVECPPDLL_CLSSS_EXPORTS __declspec(dllimport)
#endif

#include "hasp_api.h"

class NATIVECPPDLL_CLSSS_EXPORTS HaspTestNative
{
public:
    HaspTestNative();
	int HaspCheck(int feature);

private:
	hasp_handle_t handle;
	int status;

};