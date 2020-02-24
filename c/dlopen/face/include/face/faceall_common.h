/*
 * @file   faceall_common.h
 * @Author Faceall Group Limited
 * @brief  Common header for Faceall C API.
 *
 * Copyright (c) 2015-2016, Faceall Group Limited. All Rights Reserved.
 */

#ifndef FACEALL_COMMON_H_
#define FACEALL_COMMON_H_

#ifndef __cplusplus
#define FACEALL_SDK_INTERFACE extern "C"
#else
#define FACEALL_SDK_INTERFACE
#endif 

typedef int faceall_result_t;
typedef void* faceall_handle_t;

typedef struct{
	unsigned int x;		///< 点的水平方向坐标，无符号整形
	unsigned int y;		///< 点的竖直方向坐标，无符号整形
}faceall_pointi_t;

typedef struct{
	unsigned int left;		///< 矩形最左边的坐标
	unsigned int right;		///< 矩形最右边的坐标
	unsigned int top;		///< 矩形最上边的坐标
	unsigned int bottom;	///< 矩形最下边的坐标
}faceall_rect_t;

typedef struct{
	unsigned int height;	///< 图片高度
	unsigned int width;		///< 图片宽度
	unsigned int channels;	///< 图片通道数, 只支持单通道和三通道(RGB)
	unsigned char *data;	///< 图片数据, 大小为width*height*channels字节，Linux上存储顺序与OpenCV一致
}faceall_image_t;

typedef struct{
	int n_points;				///< 特征点个数，目前只支持5点
	faceall_pointi_t* points;	///< 特征点
}faceall_landmark_t;

typedef enum{
	FACEALL_compare_type_more_accurate = 0,		///< 比较的准确率更高
	FACEALL_compare_type_faster	 				///< 比较的速度更快
}FACEALL_compare_type;

typedef struct{
	unsigned int n_id;			///< 搜索的结果数
	int *ids;					///< 搜索的结果序号
	float* scores;				///< 搜索的结果的分数
}faceall_search_result_t;

#define FACEALL_OK (0)
#define FACEALL_E_FAIL (-1)
#define FACEALL_E_FAIL_TO_ALLOCATE_MEMORY (-2)
#define FACEALL_E_CANT_OPEN_FILE (-3)
#define FACEALL_E_WRONG_VALUE (-4)
#define FACEALL_E_WRONG_TYPE (-5)
#define FACEALL_E_HANDLE (-6)
#define FACEALL_E_LICENSE (-7)

#define FACEALL_ENV_NAME "FACE_MODEL_PATH"

#endif
