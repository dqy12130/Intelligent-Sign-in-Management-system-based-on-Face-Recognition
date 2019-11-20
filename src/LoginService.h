/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     LogInService.h                                                  *
*  @brief    LogIn面板的Service层实现                                          *
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
*  2019/09/10 | 1.0.0.1   | Qiyao.Dai,Zixuan.Zhao    | Create file           *
*----------------------------------------------------------------------------*
*  2019/11/13 | 1.0.0.1   | Zixuan.Zhao    | Add function 'getLabInfo'       *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef LOGINSERVICE_H
#define LOGINSERVICE_H

#include "LogInDao.h"
#include "TeacherInfo.h"
#include<LabInfo.h>
/**
 * @brief LogInService类
 * LogIn面板的Service层，用以初始化DAO层，判断是否登录成功，获取教师信息
 */
class LogInService
{
public:
    LogInService();
    ~LogInService();
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
    LogInDao* logInDao;     ///< DAO层

};

#endif // LOGINSERVICE_H
