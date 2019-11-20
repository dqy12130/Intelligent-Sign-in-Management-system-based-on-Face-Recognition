/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     UpdateService.cpp                                               *
*  @brief    Update对话框的Service层实现                                       *
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

#include "UpdateService.h"
UpdateService::UpdateService()
{
    updateDao=new UpdateDao();
    handle=ArcSoftFaceUtils::Init();
}

UpdateService::~UpdateService()
{
    ArcSoftFaceUtils::Uninit(handle);
    delete updateDao;
}

/**
 * @brief 修改学生的信息
 * @param oldStudentId 学生的原学号
 * @param newStuInfo 修改后的所有信息
 */
void UpdateService::update(QString oldStudentId, StudentInfo newStuInfo)
{
    QByteArray byteArray=ArcSoftFaceUtils::FaceFeatureExtract(handle,newStuInfo.getFaceImage(),false);
    newStuInfo.setFaceFeature(byteArray);
    updateDao->update(oldStudentId,newStuInfo);
}
