/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019   Qiyao.Dai     2650822367@qq.com                      *
*                       Zixuan.Zhao   zxZhao1998@gmail.com                   *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     ArcSoftFaceUtils.h                                              *
*  @brief    基于虹软公司(www.arcsoft.com.cn)人脸识别SDk的API接口的封装内容       *
*                                                                            *
*  @author   Qiyao Dai,Zixuan Zhao                                           *
*  @email    2650822367@qq.com,zxZhao1998@gmail.com                          *
*  @version  1.0.0.1                                                         *
*  @date                                                                     *
*  @license  GNU General Public License (GPL)                                *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2019/09/10 | 1.0.0.1   | Qiyao Dai      | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef ARCSOFTFACEUTILS_H
#define ARCSOFTFACEUTILS_H

#include <QByteArray>
#include <QImage>
//-----------------------ArcSoft-------------------------------//
#include "arcsoft_face_sdk.h"
#include "amcomdef.h"
#include "asvloffscreen.h"
#include "merror.h"
//-----------------------OpenCv-------------------------------//
#include "opencv.hpp"
//------------------------------------------------------------//
#include<ImageFromat.h>//图片格式转换
/**
 * @brief ArcSoftFaceUtils类
 * 提供人脸识别的一系列的静态函数
 */
class ArcSoftFaceUtils
{
public:
    ArcSoftFaceUtils();
    ~ArcSoftFaceUtils();
public:
    /**
     * @brief 初始化引擎
     * @return 返回引擎句柄
     */
    static MHandle Init();
    /**
     * @brief 计算人脸特征值
     * @param handle 引擎句柄
     * @param image 图片
     * @param isProcess 是否进行活体检测
     * @return 特征值
     */
    static QByteArray FaceFeatureExtract(MHandle handle, QImage image,bool isProcess);
    /**
     * @brief 计算人脸特征值
     * @param handle 引擎句柄
     * @param imgByteArray 图片的字节序列
     * @return 人脸特征值
     */
    static QByteArray FaceFeatureExtract(MHandle handle,QByteArray imgByteArray,bool isProcess);
    /**
     * @brief 特征值比对
     * @param handle 引擎句柄
     * @param feature1 特征值1
     * @param feature2 特征值2
     * @param isProcess 是否进行活体检测
     * @return 相似度
     */
    static float FaceFeatureCompare(MHandle handle,QByteArray feature1,QByteArray feature2);
    /*
     *   Qiyao Dai
     * @brief RGB活体检测
     * @param handle 引擎句柄 ，img  待检测的一帧图片，faceInfo  多人脸信息
     * @return 返回检测结果，需要调用isLiveIRjie接口得到最终结果（两个函数的句柄要相同）
    */
    static bool LiveDetect(MHandle handle ,IplImage* img,ASF_MultiFaceInfo& faceInfo);//活体检测
    /*
     *   Qiyao Dai
     * @brief RGB活体检测
     * @param handle 引擎句柄 ，img  待检测的一帧图片，faceInfo  多人脸信息
     * @return 返回检测结果，需要调用isLiveIRjie接口得到最终结果（两个函数的句柄要相同）
    */
    static bool LiveDetect(MHandle handle,QImage& img,ASF_MultiFaceInfo& faceInfo);//活体检测

    /*
     *   Qiyao Dai
     * @brief IR活体检测
     * @param handle 引擎句柄 ，img  待检测的一帧图片，faceInfo  多人脸信息
     * @return 返回检测结果，需要调用isLiveIRjie接口得到最终结果（两个函数的句柄要相同）
    */
    static bool LiveIRDetect( MHandle handle,IplImage* img,ASF_MultiFaceInfo &faceINfo);//IR活体检测
    /*
     *   Qiyao Dai
     * @brief IR活体检测
     * @param handle 引擎句柄 ，img  待检测的一帧图片，faceInfo  多人脸信息
     * @return 返回检测结果，需要调用isLiveIRjie接口得到最终结果（两个函数的句柄要相同）
    */
    static bool LiveIRDetect( MHandle handle ,QImage& img,ASF_MultiFaceInfo &faceInfo);//IR活体检测
    /**  Zixuan Zhao
     * @brief 是否通过RGB活体检测
     * @param handle 引擎句柄
     * @return 是否通过
    */
    static bool isLive(MHandle RGBhandle);//活体检测结果
    /**  Qiyao Dai
     * @brief 是否通过IR活体检测
     * @param handle 引擎句柄
     * @return 是否通过
    */
    static bool isLiveIR(MHandle IRhandle);//IR活体检测结果

    /**
     * @brief 反初始化
     * @param handle 引擎句柄
     */
    static void Uninit(MHandle handle);
private:
    /**
     * @brief 裁剪图片
     * @param 源图片
     * @param 目标图片
     * @param x 裁剪位置x
     * @param y 裁剪位置y
     */
    static void CutIplImage(IplImage* src, IplImage* dst, int x, int y);
    /**
     * @brief 将QImage图片转换为IplImage格式
     * @param qImage QImage格式图片
     * @return IplImage格式图片
     */
    static IplImage *QImageToIplImage(const QImage *qImage);
};

#endif // ARCSOFTFACEUTILS_H
