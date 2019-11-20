/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     AddService.cpp                                                  *
*  @brief    Add对话框的Service层实现                                          *
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

#include "AddService.h"

AddService::AddService()
{
    addDao=new AddDao();
    handle=ArcSoftFaceUtils::Init();
}

AddService::~AddService()
{
    ArcSoftFaceUtils::Uninit(handle);
    delete addDao;
}
/**
 * @brief 添加学生
 * @param stuInfo 学生信息
 */
void AddService::add(StudentInfo stuInfo)
{
    //计算特征值并写入stuInfo
    QByteArray byteArray=ArcSoftFaceUtils::FaceFeatureExtract(handle,stuInfo.getFaceImage(),false);
    stuInfo.setFaceFeature(byteArray);
    //添加
    addDao->add(stuInfo);
}
