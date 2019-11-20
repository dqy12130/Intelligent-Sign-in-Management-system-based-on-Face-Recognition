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
//#include<lib/opencv/include/opencv2/opencv.hpp>
#include<opencv.hpp>
//------------------------------------------------------------//


class ArcSoftFaceUtils
{
public:
    ArcSoftFaceUtils();
    ~ArcSoftFaceUtils();
public:
    //初始化引擎
    static MHandle Init();
    static MHandle InitComere();
    //获取人脸特征值
    static QByteArray FaceFeatureExtract(MHandle handle, QImage image);
    static QByteArray FaceFeatureExtract(MHandle handle,QByteArray imgByteArray);
    //特征值比对
    static float FaceFeatureCompare(MHandle handle,QByteArray feature1,QByteArray feature2);
    //反初始化
    static void Uninit(MHandle handle);
private:
    //裁剪图片,做四字节对齐
    static void CutIplImage(IplImage* src, IplImage* dst, int x, int y);
    //QImage转IplImage
    static IplImage *QImageToIplImage(const QImage *qImage);
};

#endif // ARCSOFTFACEUTILS_H
