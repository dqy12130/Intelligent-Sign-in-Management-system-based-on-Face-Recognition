/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     SignInService.cpp                                               *
*  @brief    SignIn面板的Service层实现                                         *
*                                                                            *
*  @author   Zixuan Zhao                                                     *
*  @email    zxZhao1998@gmail.com                                            *
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
*  2019/09/10 | 1.0.0.1   | Zixuan.Zhao    | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#include "SignInService.h"
#include <QDebug>
SignInService::SignInService(int labId)
{
    //初始化Dao层
    signDao=new SignInDao();
    //初始化人脸库
    studentsInfo=signDao->getAllStuInfo(labId);
    //初始化引擎
    handle=ArcSoftFaceUtils::Init();
}

SignInService::~SignInService()
{
    //反初始化引擎
    ArcSoftFaceUtils::Uninit(handle);
    delete signDao;
}

/**
 * @brief 图片的处理Slot
 * @param image 待处理的图片
 */
void SignInService::receiveImage(QImage image)
{
    //提取图片中人脸的特征值
    QByteArray feature=ArcSoftFaceUtils::FaceFeatureExtract(handle,image,true);
    //如果特征值为空，表示图片中未检测到人脸
    if(feature.isEmpty())
    {
        emit sendResult("未检测到人脸...");
        return;
    }
    if(ArcSoftFaceUtils::isLive(handle)==false)
    {
        emit sendResult("活体检测未通过！");
        return;
    }
    //如果为空，表示未检测到人脸
    if(feature.isEmpty())
    {
        emit sendResult("请对准摄像头");
    }
    double MaxResult=0;
    double SimarThreshold=0.75;
    QString maxSimarId;
    StudentInfo ResultInfo;
    double tempResult;
    //将提取到的人脸在人脸库中比对
    for(StudentInfo stuItem:studentsInfo)
    {
        tempResult=ArcSoftFaceUtils::FaceFeatureCompare(handle,feature,stuItem.getFaceFeature());

//        if(tempResult>=SimarThreshold)
//        {
//            MaxResult=tempResult;
//            maxSimarId=stuItem.getName();//记录可信度最高的人的ID
//            ResultInfo=stuItem;
//        }
        if(tempResult>=0.90)
        {
            MaxResult=tempResult;
            maxSimarId=stuItem.getName();//记录可信度最高的人的ID
            ResultInfo=stuItem;
            break;//可信度非常高，退出
        }
    }
    if(ResultInfo.isEmpty()==false)
    {
        //比对成功，查看此人是否已签到，如果未签到，则进行签到
        if(signDao->isSignInSuccess(ResultInfo.getStudentId())==true)
        {
            //如果已经签到
            emit sendResult(QString("姓名:%1\n性别:%2\n学号:%3\n签到状态:今日已签").arg(ResultInfo.getName()).arg(ResultInfo.getSex()).arg(ResultInfo.getStudentId()));
        }
        else
        {
            emit sendResult(ResultInfo.getName()+" 签到成功!");
        }
    }
    else
    {
        emit sendResult("陌生人...");
    }
}

