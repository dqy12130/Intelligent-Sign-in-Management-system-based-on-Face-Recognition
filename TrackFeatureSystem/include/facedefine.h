#ifndef FACEDEFINE_H
#define FACEDEFINE_H
#include<arcsoft_face_sdk.h>

enum MASKS
{
    FACE_NORE_MASK	=0x00000000,
    FACE_DETECT		=0x00000001,
    FACE_RECOGNITION=	0x00000004,
    FACE_AGE		=		0x00000008,
    FACE_GENDER		=	0x00000010,
    FACE_3DANGLE	=	0x00000020,
    FACE_LIVENESS	=	0x00000080,
    FACE_IR_LIVENESS=		0x00000400,
    FACE_DETECT_VIDEO_MODE =0x00000000,
    FACE_DETECT_IMAGE_MODE =0xFFFFFFFF
};

enum FaceDetectMode
{
   VIDEO_MODE =0x00000000,
   IMAGE_MODE =0xFFFFFFFF
};


typedef  ASF_FaceFeature  FaceFeature ;
#ifdef __cplusplus
extern "C" {
#endif

/* MASK（功能集）   */
/*
#define FACE_NORE_MASK				0x00000000	//无属性
#define FACE_DETECT			0x00000001	//此处detect可以是tracking或者detection两个引擎之一，具体的选择由detect mode 确定
#define FACE_RECOGNITION		0x00000004	//人脸特征
#define FACE_AGE					0x00000008	//年龄
#define FACE_GENDER				0x00000010	//性别
#define FACE_3DANGLE			0x00000020	//3D角度
#define FACE_LIVENESS			0x00000080	//RGB活体
#define FACE_IR_LIVENESS			0x00000400	//红外活体
#define FACE_DETECT_VIDEO_MODE 	0x00000000		//Video模式，一般用于多帧连续检测
#define FACE_DETECT_IMAGE_MODE	0xFFFFFFFF		//Image模式，一般用于静态图的单次检测
*/



}

#ifdef __cplusplus
#endif

#endif // FACEDEFINE_H
