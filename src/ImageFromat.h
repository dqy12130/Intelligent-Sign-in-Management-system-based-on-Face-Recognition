
/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     imageFromat.h                                                   *
*  @brief    opencv库与Qt库常用图片格式的转换                                   *
*                                                                            *
*  @author   Qiyao Dai                                                       *
*  @email   2650822367@qq.com                                                *
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
*  2019/010/10 | 1.0.0.1   |Qiyao Dai      | Create file                     *
*----------------------------------------------------------------------------*
*  2019/11/13 | 1.0.0.1   | Qiyao Dai      | Add function 'QByteArrayToIple  *
*             |           |                |    Imag   '                     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef IMAGEFROMAT_H
#define IMAGEFROMAT_H
/*opencv基础库头文件*/
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/video.hpp>
#include<opencv2/videoio.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<QMutex>//原子变量头文件
      /*第三方库头文件*/
#include<asvloffscreen.h>
#include<amcomdef.h>
#include<arcsoft_face_sdk.h>
#include<merror.h>
     /*Qt框架头文件*/
#include<QByteArray>
#include<QBuffer>
#include<QDebug>
#include<QPixmap>
#include<QPainter>
#include<QImage>

class ImageFromat
{
public:
    /*OPenCV和Qt图片格式的相互转换*/
    static QPixmap MatToQPixMap( const cv::Mat& frame);//Mat转QPixmap
    static QImage MatToQImage  (const cv::Mat &frame);//Mat转QImage
    static  QByteArray MatToQByteArray(const cv::Mat& frame);//Map转QByteArray
    /*OPenCV和Qt图片格式的相互转换*/
    static cv::Mat  QPixmapToMat(const QPixmap&);//QPixmap转Mat
    static cv::Mat QImageToMat(const QImage&);//QImage转Mat
    static cv::Mat QByteArrayToMat(const QByteArray&);//QByteArray转Mat

    /*OPenCV和Qt图片格式的相互转换*/
    static IplImage QPixmapToIplImage(const QPixmap&);//QPixmap转IplImage
    static IplImage QImageToIplImage(const QImage&);//QImage转IplImage
    static IplImage QByteArrayToIplImage(const QByteArray&);//QByteArray转IplImage

    /*QPixmap 和QImage互转*/
    static QImage QPixmapToQImage(QPixmap);
    static QPixmap  QImageToQPixmap(QImage);

    /*OPenCVMat和IplImage相互转换*/
    static cv::Mat IplImageToMat(const IplImage&);//IplImage转Mat
    static IplImage MatToIplImage(const cv::Mat&);//Mat转IplImage

    static bool MatIsNull(const cv::Mat &mat);//判断Mat是否为空
    static bool IplImageIsNull(const IplImage & img);//判断IplImage是否为空
    static bool QPixmapIsNull(const QPixmap & Pixmap);//判断QPixmap是否为空
    static bool QImageIsNull(const QImage &img);//判断QImage是否为空
    static bool QByteArrayIsNull(const QByteArray & byte);//判断QByteArray内的数据是否为空

};



#endif // IMAGEFROMAT_H
