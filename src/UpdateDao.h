/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     UpdateDao.h                                                     *
*  @brief    Update对话框的DAO层实现                                           *
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

#ifndef UPDATEDAO_H
#define UPDATEDAO_H

#include "StudentInfo.h"
#include "MySqlUtils.h"

/**
 * @brief UpdateDao类
 * 属于Update对话框的DAO层，提供数据库交互接口
 */
class UpdateDao
{
public:
    UpdateDao();
    ~UpdateDao();
public:
    /**
     * @brief 修改学生的信息
     * @param oldStudentId 学生的原学号
     * @param newStuInfo 修改后的所有信息
     */
    void update(QString oldStudentId,StudentInfo newStuInfo);
private:
    QSqlDatabase db;        ///< 数据库引擎
};

#endif // UPDATEDAO_H
