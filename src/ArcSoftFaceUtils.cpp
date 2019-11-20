/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019   Qiyao.Dai     2650822367@qq.com                      *
*                       Zixuan.Zhao   zxZhao1998@gmail.com                   *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     ArcSoftFaceUtils.cpp                                             *
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

#include "ArcSoftFaceUtils.h"
#include <QDebug>

//-----------------------------------------------------------------------
// SDK APPID and SDKKey
//-----------------------------------------------------------------------
#define APPID "Eii53vmytpf6cZAbjpeFJtFYapM7DvvSPRBJiGo8L6dN"
#define SDKKey "ByBe35STYrj2c8uT48CULeea6SCvaHkfd5nJ4yFX57GK"
//----------------------------------------------------------------------
// Safe memery manage
//----------------------------------------------------------------------
#define SafeFree(p) { if ((p)) free(p); (p) = NULL; }
#define SafeArrayDelete(p) { if ((p)) delete [] (p); (p) = NULL; }
#define SafeDelete(p) { if ((p)) delete (p); (p) = NULL; }

ArcSoftFaceUtils::ArcSoftFaceUtils()
{
    
}

ArcSoftFaceUtils::~ArcSoftFaceUtils()
{
    
}

/**
 * @brief 初始化引擎
 * @return 返回引擎句柄
 */
MHandle ArcSoftFaceUtils::Init()
{
    //激活接口,需联网激活
    MRESULT res = ASFOnlineActivation(APPID, SDKKey);
    //MRESULT res = ASFActivation(APPID, SDKKey);
    if (MOK != res && MERR_ASF_ALREADY_ACTIVATED != res)
    {
        qDebug()<<"ASFActivation fail:"<<res;
    }
    else
    {
        qDebug()<<"ASFActivation sucess:"<<res;
    }
    
    //获取激活文件信息
    ASF_ActiveFileInfo  activeFileInfo;
    res = ASFGetActiveFileInfo(&activeFileInfo);
    if (res != MOK)
    {
        qDebug()<<"ASFGetActiveFileInfo fail:"<<res;
    }
    else
    {
        qDebug()<<"ASFGetActiveFileInfo success:"<<res;
    }
    
    //初始化引擎
    MHandle handle = nullptr;
    MInt32 mask = ASF_FACE_DETECT | ASF_FACERECOGNITION  | ASF_LIVENESS ;
    //video模式
    res = ASFInitEngine(ASF_DETECT_MODE_IMAGE, ASF_OP_0_ONLY, 30, 10, mask, &handle);
    if (res != MOK)
        qDebug()<<"ASFInitEngine fail:"<<res;
    else
        qDebug()<<"ASFInitEngine sucess:"<<res;
    
    return handle;
}

/**
 * @brief 计算人脸特征值
 * @param handle 引擎句柄
 * @param image 图片
 * @param isProcess 是否进行活体检测
 * @return 特征值
 */
QByteArray ArcSoftFaceUtils::FaceFeatureExtract(MHandle handle,QImage image,bool isProcess)
{
    QByteArray but;//默认为空
    IplImage* img =QImageToIplImage(&image);
    //多人脸信息
    ASF_MultiFaceInfo detectedFaces={ 0 };
    //单人脸信息
    ASF_SingleFaceInfo SingleDetectedFace = { 0 };
    //人脸特征
    ASF_FaceFeature feature = { 0 };
    //拷贝的人脸特征
    ASF_FaceFeature copyfeature = { 0 };
    //预分配裁剪后的图像首地址，并分配存储空间
    IplImage* cutImg = cvCreateImage(cvSize(img->width - img->width % 4, img->height), IPL_DEPTH_8U, img->nChannels);
    //裁剪
    CutIplImage(img, cutImg, 0, 0);
    //人脸检测
    MRESULT res = ASFDetectFaces(handle, cutImg->width, cutImg->height, ASVL_PAF_RGB24_B8G8R8, (MUInt8*)cutImg->imageData, &detectedFaces);
    //判断是否检测到人脸
    if (MOK == res)
    {
        //从多人脸信息中获取单人脸信息
        SingleDetectedFace.faceRect.left = detectedFaces.faceRect[0].left;
        SingleDetectedFace.faceRect.top = detectedFaces.faceRect[0].top;
        SingleDetectedFace.faceRect.right = detectedFaces.faceRect[0].right;
        SingleDetectedFace.faceRect.bottom = detectedFaces.faceRect[0].bottom;
        SingleDetectedFace.faceOrient = detectedFaces.faceOrient[0];

        //单人脸特征提取
        res = ASFFaceFeatureExtract(handle, cutImg->width, cutImg->height, ASVL_PAF_RGB24_B8G8R8, (MUInt8*)cutImg->imageData, &SingleDetectedFace, &feature);
        //判断是否提取成功
        if (res == MOK)
        {
            //拷贝feature
            copyfeature.featureSize = feature.featureSize;
            copyfeature.feature = (MByte *)malloc(feature.featureSize);
            memset(copyfeature.feature, 0, feature.featureSize);
            memcpy(copyfeature.feature, feature.feature, feature.featureSize);
        }
        else
            qDebug()<<"ASFFaceFeatureExtract 1 fail:"<<res;
    }
    else
    {  qDebug()<<"ASFDetectFaces 1 fail: %d\n"<<res;
        return but;
    }

    bool flag=ArcSoftFaceUtils::LiveDetect(handle,cutImg,detectedFaces);
    if(flag==false)
    {
        return  but;
    }
    //转为ByteArra
    QByteArray faceFeature((char*)copyfeature.feature,copyfeature.featureSize);
    //释放内存
    SafeFree(copyfeature.feature);
    cvReleaseImage(&img);
    return faceFeature;
}


/**
 * @brief 计算人脸特征值
 * @param handle 引擎句柄
 * @param imgByteArray 图片的字节序列
 * @return 人脸特征值
 */
QByteArray ArcSoftFaceUtils::FaceFeatureExtract(MHandle handle, QByteArray imgByteArray,bool isProcess)
{
    QImage image;
    image.loadFromData(imgByteArray,"PNG");
    return FaceFeatureExtract(handle,image,isProcess);
}


/**
 * @brief 特征值比对
 * @param handle 引擎句柄
 * @param feature1 特征值1
 * @param feature2 特征值2
 * @return 相似度
 */
float ArcSoftFaceUtils::FaceFeatureCompare(MHandle handle, QByteArray feature1, QByteArray feature2)
{
    ASF_FaceFeature f1 = { 0 };
    ASF_FaceFeature f2 = { 0 };
    
    //初始化f1
    f1.featureSize=feature1.size();
    f1.feature=(MByte*)feature1.data();
    
    //初始化f2
    f2.featureSize=feature2.size();
    f2.feature=(MByte*)feature2.data();
    
    //单人脸特征比对
    MFloat confidenceLevel;
    MRESULT res = ASFFaceFeatureCompare(handle, &f1, &f2, &confidenceLevel);
    if (res != MOK)
    {
        qDebug()<<"ASFFaceFeatureCompare fail:"<<res;
    }
    else
        qDebug("ASFFaceFeatureCompare sucess:%lf",confidenceLevel);
    
    return confidenceLevel;
}


/*
 * * @brief RGB活体检测
 * @param handle RGB引擎句柄
 * @param liveImg 待检测图片
 * @param faceInfo  多人脸信息
 * @return ASFProcess运行结果
*/
bool ArcSoftFaceUtils::LiveDetect(MHandle hEngine,IplImage* liveImg,ASF_MultiFaceInfo &faceInfo)//活体检测
{
    MInt32 LiveMask = ASF_LIVENESS;
    ASF_MultiFaceInfo detectedFaces=faceInfo;
    ASF_LivenessThreshold LivenessThreshold;
    LivenessThreshold.thresholdmodel_BGR=0.75;
    LivenessThreshold.thresholdmodel_IR=0.7;
    MRESULT res=ASFSetLivenessParam(hEngine,&LivenessThreshold);
    qDebug()<<"ASFSetLivenessParam"<<res;
    res = ASFProcess(hEngine, liveImg->width, liveImg->height, ASVL_PAF_RGB24_B8G8R8,
                     (MUInt8*)liveImg->imageData, &detectedFaces,LiveMask);
    bool returnFlag=false;
    if(res==MOK)
    {
        returnFlag=true;
    }
    return returnFlag;
}

/*
 * * @brief RGB活体检测
 * @param handle RGB引擎句柄
 * @param image 待检测图片
 * @param faceInfo  多人脸信息
 * @return ASFProcess运行结果
*/
bool ArcSoftFaceUtils::LiveDetect(MHandle hEngine,QImage &image,ASF_MultiFaceInfo& faceInfo)//活体检测
{
    IplImage* liveImg=QImageToIplImage(&image);
    return  LiveDetect(hEngine,liveImg,faceInfo);
}

/*
 * * @brief IR活体检测
 * @param handle IR引擎句柄
 * @param image 待检测图片
 * @param faceInfo  多人脸信息
 * @return ASFProcess_IR运行结果
*/
bool ArcSoftFaceUtils::LiveIRDetect( MHandle handle,IplImage*liveImg ,ASF_MultiFaceInfo &faceInfo)//LiveIRDetect活体检测
{
    cv::Mat matImg=ImageFromat::IplImageToMat(*liveImg);//IplImage转Mat 设为ture为深拷贝
    cv::cvtColor(matImg, matImg, CV_BGR2GRAY);
    IplImage iplGrayMat =((IplImage)matImg);//mat 转 IplImage 浅拷贝
    IplImage* cutGrayImg = cvCreateImage(cvSize(iplGrayMat.width - (iplGrayMat.width % 4), iplGrayMat.height), IPL_DEPTH_8U, iplGrayMat.nChannels);
    CutIplImage(&iplGrayMat, cutGrayImg, 0, 0);
    if (!cutGrayImg)
    {
        cvReleaseImage(&cutGrayImg);
        return false;
    }
    MInt32 IRLiveMask  = ASF_IR_LIVENESS;
    ASF_MultiFaceInfo detectedFaces=faceInfo;

    ASF_LivenessThreshold LivenessThreshold;
    ASF_LivenessInfo irLiveNessInfo;
    LivenessThreshold.thresholdmodel_BGR=0.75;
    LivenessThreshold.thresholdmodel_IR=0.7;
    MRESULT res=ASFSetLivenessParam(handle,&LivenessThreshold);
    res = ASFProcess_IR(handle, cutGrayImg->width, cutGrayImg->height, ASVL_PAF_GRAY,
                        (MUInt8*)cutGrayImg->imageData, &detectedFaces, IRLiveMask);
    cvReleaseImage(&cutGrayImg);

    if(res==MOK)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
 * * @brief IR活体检测
 * @param handle IR引擎句柄
 * @param image 待检测图片
 * @param faceInfo  多人脸信息
 * @return ASFProcess_IR运行结果
*/
bool ArcSoftFaceUtils::LiveIRDetect( MHandle handle,QImage &image,ASF_MultiFaceInfo &faceInfo)
{
    IplImage* liveImg=QImageToIplImage(&image);
    return  LiveIRDetect(handle,liveImg,faceInfo);
}


/**
 * @brief 是否通过RGB活体检测
 * @param handle 引擎句柄
 * @return 是否通过
 */
bool ArcSoftFaceUtils::isLive(MHandle handle)
{
    bool isLive=false;
    //获取RGB活体信息
    ASF_LivenessInfo irLivenessInfo = { 0 };
    MRESULT res=ASFGetLivenessScore_IR(handle, &irLivenessInfo);
    ASF_LivenessInfo rgbLivenessInfo = { 0 };
    res = ASFGetLivenessScore(handle, &rgbLivenessInfo);
    if (res != MOK)
        qDebug()<<"ASFGetLivenessScore fail: %d\n"<<res;
    else
    {
        qDebug()<<"RGB Liveness: %d\n"<<rgbLivenessInfo.isLive[0];
        if(rgbLivenessInfo.isLive[0]==1)
        {
            isLive=true;
        }
    }
    return isLive;
}


bool ArcSoftFaceUtils::isLiveIR(MHandle handle)
{
    bool isLive=false;
    //获取RGB活体信息
    ASF_LivenessInfo irLivenessInfo = { 0 };
    MRESULT res=ASFGetLivenessScore_IR(handle, &irLivenessInfo);

    if (res != MOK)
        qDebug()<<"ASFGetLivenessScore fail: %d\n"<<res;
    {
        qDebug()<<"IR Liveness: %d\n"<<irLivenessInfo.isLive[0];
        if(irLivenessInfo.isLive[0]==1)
        {
            isLive=true;
        }
    }
    return isLive;
}
/**
 * @brief Uninit 反初始化
 * @param handle 引擎句柄
 */
void ArcSoftFaceUtils::Uninit(MHandle handle)
{
    //反初始化
    MRESULT res = ASFUninitEngine(handle);
    if (res != MOK)
        qDebug("ALUninitEngine fail: %d\n", res);
    else
        qDebug("ALUninitEngine sucess: %d\n", res);
    
}

/**
 * @brief 裁剪图片
 * @param 源图片
 * @param 目标图片
 * @param x 裁剪位置x
 * @param y 裁剪位置y
 */
void ArcSoftFaceUtils::CutIplImage(IplImage *src, IplImage *dst, int x, int y)
{
    //区域大小
    CvSize size = cvSize(dst->width, dst->height);
    //设置源图像ROI
    cvSetImageROI(src, cvRect(x, y, size.width, size.height));
    //复制图像
    cvCopy(src, dst);
    cvResetImageROI(src);//源图像用完后，清空ROI
}

/**
 * @brief 将QImage图片转换为IplImage格式
 * @param qImage QImage格式图片
 * @return IplImage格式图片
 */
IplImage* ArcSoftFaceUtils::QImageToIplImage(const QImage * qImage)
{
    int width = qImage->width();
    int height = qImage->height();
    CvSize Size;
    Size.height = height;
    Size.width = width;
    IplImage *IplImageBuffer = cvCreateImage(Size, IPL_DEPTH_8U, 3);
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            QRgb rgb = qImage->pixel(x, y);
            cvSet2D(IplImageBuffer, y, x, CV_RGB(qRed(rgb), qGreen(rgb), qBlue(rgb)));
        }
    }
    return IplImageBuffer;
}
