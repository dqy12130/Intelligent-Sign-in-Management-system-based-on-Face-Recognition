/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     UpdateService.h                                                 *
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

#ifndef UPDATESERVICE_H
#define UPDATESERVICE_H

#include "StudentInfo.h"
#include"UpdateDao.h"
#include "ArcSoftFaceUtils.h"
class UpdateService
{
public:
    UpdateService();
    ~UpdateService();

public:
    /**
     * @brief 修改学生的信息
     * @param oldStudentId 学生的原学号
     * @param newStuInfo 修改后的所有信息
     */
    void update(QString oldStudentId,StudentInfo newStuInfo);
private:
    UpdateDao* updateDao;       ///< DAO层
    MHandle handle;             ///< 人脸识别引擎句柄
};

#endif // UPDATESERVICE_H
