/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     AddDao.h                                                        *
*  @brief    Add对话框的Dao层实现                                              *
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
#ifndef ADDDAO_H
#define ADDDAO_H

#include "StudentInfo.h"
#include "MySqlUtils.h"

/**
 * @brief AddDao类
 * 属于Add对话框的Dao层，提供数据库交互接口
 */
class AddDao
{
public:
    AddDao();
    ~AddDao();
public:
    /**
     * @brief 添加学生
     * @param stuInfo 学生信息
     */
    void add(StudentInfo stuInfo);
private:
    QSqlDatabase db;    ///< 数据库引擎

};

#endif // ADDDAO_H
