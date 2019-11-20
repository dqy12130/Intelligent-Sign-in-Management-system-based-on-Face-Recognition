/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     AddService.h                                                    *
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

#ifndef ADDSERVICE_H
#define ADDSERVICE_H

#include "AddDao.h"
#include "StudentInfo.h"
#include "ArcSoftFaceUtils.h"

/**
 * @brief AddService类
 * 属于Add对话框的Service层
 */
class AddService
{
public:
    AddService();
    ~AddService();
public:
    /**
     * @brief 添加学生
     * @param stuInfo 学生信息
     */
    void add(StudentInfo stuInfo);
private:
    AddDao* addDao;         ///< DAO层
    MHandle handle;         ///< 人脸识别引擎句柄
};

#endif // ADDSERVICE_H
