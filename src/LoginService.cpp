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

#include "LogInService.h"

LogInService::LogInService()
{
    logInDao=new LogInDao();
}

LogInService::~LogInService()
{
    delete logInDao;
}

/**
 * @brief 判断是否登录成功
 * @param[in] userName 用户名
 * @param[in] password 密码
 * @return 登录结果
 */
bool LogInService::isLogInSuccess(QString userName, QString password)
{
    bool isSuccess=false;
    //调用DAO层判断登录是否成功
    isSuccess=logInDao->isLogInSuccess(userName,password);
    //返回登录结果
    return isSuccess;
}

/**
 * @brief 获取教师信息
 * @param userName 用户名
 * @return 登录教师的信息
 */
TeacherInfo LogInService::getTeacherInfo(QString userName)
{
    return logInDao->getTeacherInfo(userName);
}

/**
 * @brief 获取管辖的实验室信息
 * @param teacherId 教职工号
 * @return 所有管辖的实验室
 */
QVector<LabInfo> LogInService::getLabInfo(QString teacherId)
{
    return logInDao->getLabInfo(teacherId);
}
