/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     LogInDao.h                                                      *
*  @brief    LogIn面板的DAO层实现                                              *
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
*  2019/11/13 | 1.0.0.1   | Zixuan.Zhao    | Add function 'getLabInfo'       *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef LOGINDAO_H
#define LOGINDAO_H
#include "TeacherInfo.h"
#include "LabInfo.h"
#include "MySqlUtils.h"
#include <QString>
/**
 * @brief LogInDao类
 * 属于LogIn面板的DAO层，用以提供数据库交互接口，包括根据UserName和Password判断是否登录成功，获取UserName对应的教师信息
 */
class LogInDao
{
public:
    LogInDao();
    ~LogInDao();
public:
    /**
     * @brief 判断是否登录成功
     * @param[in] userName 用户名
     * @param[in] password 密码
     * @return 登录结果
     */
    bool isLogInSuccess(QString userName,QString password);
    /**
     * @brief 获取教师信息
     * @param userName 用户名
     * @return 登录教师的信息
     */
    TeacherInfo getTeacherInfo(QString userName);

    /**
     * @brief 获取管辖的实验室信息
     * @param teacherId 教职工号
     * @return 所有管辖的实验室
     */
    QVector<LabInfo> getLabInfo(QString teacherId);
private:
   QSqlDatabase db;     ///< 数据库引擎
};

#endif // LOGINDAO_H
